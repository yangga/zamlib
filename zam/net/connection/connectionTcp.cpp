//
// Created by SungWoo Yang on 2017. 9. 19..
//

#include "connectionTcp.h"

#include <zam/base/exception.h>
#include <zam/base/logger.h>

namespace zam {
    namespace net {
        namespace connection {

            connectionTcp::connectionTcp(base::io::ioSystem& ios)
                    : connection(ios)
                    , sock_(ios.getIos())
                    , offset_(0)
                    , status_(status::close)
            {}

            endPoint connectionTcp::remote_endpoint() {
                return endPoint{ sock_.remote_endpoint().address().to_string(), sock_.remote_endpoint().port() };
            }

            void connectionTcp::startAccept() {
                sock_.set_option(boost::asio::ip::tcp::no_delay(true));
                sock_.set_option(boost::asio::socket_base::linger(true, 0));

                offset_ = 0;
                startRead();

                status_ = status::open;
            }

            void connectionTcp::startConnect() {
                sock_.set_option(boost::asio::ip::tcp::no_delay(true));
                sock_.set_option(boost::asio::socket_base::linger(true, 0));

                offset_ = 0;
                startRead();

                status_ = status::open;
            }

            void connectionTcp::closing() {
                closing(boost::asio::ip::tcp::socket::shutdown_receive);
            }

            void connectionTcp::startRead() {

                boost::function<void(const boost::system::error_code& ec, size_t bytes_transferred)> readLambda (
                        [s=shared_from_this()](const boost::system::error_code& ec, size_t bytes_transferred) {
                            s->toChild<connectionTcp>().readHandler(ec, bytes_transferred);
                        });

                sock_.async_read_some(
                        boost::asio::buffer(msg_.ptr()+offset_, msg_.size()-offset_)
                        , strand().wrap(
                                boost::bind(
                                        readLambda
                                        , boost::asio::placeholders::error
                                        , boost::asio::placeholders::bytes_transferred)));
            }

            void connectionTcp::readHandler(const boost::system::error_code& ec, size_t bytes_transferred) {
                if (!ec) {
                    assert(0 < bytes_transferred);
                    offset_ += bytes_transferred;

                    try {
                        do {
                            if (packer_) {
                                auto unpackLambda = [this](message& msgUnpacked)
                                {
                                    messageIStream isUnpack(msg_, offset_);
                                    const auto msgUnpackedLen = packer()->unpack(msgUnpacked, isUnpack);
                                    assert(offset_ >= isUnpack.readSize());
                                    offset_ -= isUnpack.readSize();
                                    msg_.squash(isUnpack.readSize(), isUnpack.dataSize()-isUnpack.readSize());
                                    return msgUnpackedLen;
                                };

                                if (cipher_) {
                                    message msgUnpacked;
                                    const auto msgUnpackedLen = unpackLambda(msgUnpacked);

                                    auto msgDecrypted = boost::make_shared<message>();
                                    messageIStream isDecrypt(msgUnpacked, msgUnpackedLen);
                                    const auto msgDecryptedLen = cipher_->decrypt(*msgDecrypted, isDecrypt);

                                    ioPost(
                                            boost::bind(
                                                    &handler::eventHandler::onRecv
                                                    , eventHandler()
                                                    , shared_from_this()
                                                    , msgDecrypted
                                                    , msgDecryptedLen
                                            ));
                                }
                                else {
                                    auto msgUnpacked = boost::make_shared<message>();
                                    const auto msgUnpackedLen = unpackLambda(*msgUnpacked);

                                    ioPost(
                                            boost::bind(
                                                    &handler::eventHandler::onRecv
                                                    , eventHandler()
                                                    , shared_from_this()
                                                    , msgUnpacked
                                                    , msgUnpackedLen
                                            ));
                                }
                            }
                            else {
                                auto msgToss = boost::make_shared<message>();
                                messageOStream os(*msgToss);
                                os.write(msg_.ptr(), offset_);

                                ioPost(
                                        boost::bind(
                                                &handler::eventHandler::onRecv
                                                , eventHandler()
                                                , shared_from_this()
                                                , msgToss
                                                , offset_
                                        ));

                                offset_ = 0;
                            }
                        }while (0 < offset_);

                        startRead();
                    }
                    catch(zam::base::zamException& e) {
                        if (netError::incompleted_packet == e.errorNo()) {
                            startRead();
                        }
                        else {
                            ZAM_LOGD("default") << "connectionTcp::readHandler -"
                                                << " exception:" << e.errorNo()
                                                << ", msg:" << e.what();
                            closing();
                        }
                    } catch(std::exception& e) {
                        ZAM_LOGD("default") << "exception in connectionTcp::readHandler - " << e.what();
                        closing(boost::asio::ip::tcp::socket::shutdown_receive);
                    }
                }
                else {
                    closing(boost::asio::ip::tcp::socket::shutdown_receive);
                }
            }

            void connectionTcp::closing(boost::asio::socket_base::shutdown_type what) {
                boost::system::error_code ec;
                sock_.shutdown(what, ec);

                if (status_ == status::open) {
                    status_ = status::closing;

                    if (ec && boost::system::errc::not_connected != ec.value()) {
                        ZAM_LOGW("default") << "shutdown error -"
                                    << " what:" << what
                                    << ", msg:" << ec.message();
                    }

                    ioPost(
                            [s=shared_from_this()]() {
                                s->toChild<connectionTcp>().close();
                            });
                }
            }

            void connectionTcp::close() {
                boost::system::error_code ec;
                sock_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

                if (status_ != connection::status::close) {
                    status_ = connection::status::close;

                    if (ec && boost::system::errc::not_connected != ec.value()) {
                        ZAM_LOGW("default") << "shutdown error - " << ec.message();
                    }

                    ioPost(
                            boost::bind(
                                    &handler::eventHandler::onClose
                                    , eventHandler()
                                    , shared_from_this()));
                }
            }

            void connectionTcp::send(message& msg, size_t msg_len) {
                try {
                    if (packer_) {
                        auto packNsend = [this](message& m, size_t len)
                        {
                            message msgPacked;
                            messageIStream isPack(m, len);
                            auto msgPackedLen = packer_->pack(msgPacked, isPack);
                            sendRaw(msgPacked.ptr(), msgPackedLen);
                        };

                        if (cipher_) {
                            message msgEncrypted;
                            messageOStream osEncrypt(msg, msg_len);
                            auto msgEncryptedLen = cipher_->encrypt(msgEncrypted, osEncrypt);

                            packNsend(msgEncrypted, msgEncryptedLen);
                        }
                        else {
                            packNsend(msg, msg_len);
                        }
                    }
                    else {
                        sendRaw(msg.ptr(), msg_len);
                    }
                } catch(base::zamException& e) {
                    ZAM_LOGD("default") << "connectionTcp::send exception -"
                                        << " exception:" << e.errorNo()
                                        << ", msg:" << e.what();
                    closing(boost::asio::ip::tcp::socket::shutdown_send);
                } catch(std::exception& e) {
                    ZAM_LOGD("default") << "connectionTcp::send exception -"
                                        << " msg:" << e.what();
                    closing(boost::asio::ip::tcp::socket::shutdown_send);
                }
            }

            void connectionTcp::sendRaw(void* src, size_t src_len) {
                boost::function<void(const boost::system::error_code& ec, size_t bytes_transferred)> writeLambda (
                        [s=shared_from_this()](const boost::system::error_code& ec, size_t bytes_transferred) {
                            s->toChild<connectionTcp>().writeHandler(ec, bytes_transferred);
                        });

                boost::asio::async_write(
                        sock_
                        , boost::asio::buffer(src, src_len)
                        , strand().wrap(boost::bind(
                                writeLambda
                                , boost::asio::placeholders::error
                                , boost::asio::placeholders::bytes_transferred))
                );
            }

            void connectionTcp::writeHandler(const boost::system::error_code& ec, size_t bytes_transferred) {
                if (!ec) {
                    return;
                }

                closing(boost::asio::ip::tcp::socket::shutdown_send);
            }

        }
    }
}

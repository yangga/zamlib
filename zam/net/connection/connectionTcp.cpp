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

            void connectionTcp::closing() {
                closing(boost::asio::ip::tcp::socket::shutdown_receive);
            }

            void connectionTcp::startRead() {

                boost::function<void(const boost::system::error_code& ec, size_t bytes_transferred)> readLambda (
                        [s=shared_from_this()](const boost::system::error_code& ec, size_t bytes_transferred) {
                            dynamic_cast<connectionTcp*>(s.get())->readHandler(ec, bytes_transferred);
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
                offset_ += bytes_transferred;

                if (!ec) {
                    messageIStream is(msg_, offset_);

                    auto msgUnpacked = boost::make_shared<message>();
                    try {
                        const auto msgUnpackedLen = packer()->unpack(*msgUnpacked, is);
                        assert(offset_ >= is.readSize());
                        offset_ -= is.readSize();
                        msg_.squash(is.readSize(), is.dataSize()-is.readSize());

                        ioPost(
                                boost::bind(
                                        &handler::eventHandler::onPacket
                                        , eventHandler()
                                        , shared_from_this()
                                        , msgUnpacked
                                        , msgUnpackedLen
                                ));

                        startRead();
                    } catch(zam::base::zamException& e) {
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

                if (!ec && status_ == status::open)
                {
                    status_ = status::closing;

                    ioPost(
                            [s=shared_from_this()]() {
                                dynamic_cast<connectionTcp*>(s.get())->close();
                            });
                }
            }

            void connectionTcp::close() {
                boost::system::error_code ec;
                sock_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

                if (!ec)
                {
                    status_ = connection::status::close;

                    ioPost(
                            boost::bind(
                                    &handler::eventHandler::onClose
                                    , eventHandler()
                                    , shared_from_this()));
                }
                else
                {
                    if (boost::system::errc::not_connected != ec.value()) {
                        ZAM_LOGD("default") << "shutdown error - " << ec.message();
                    }
                }
            }
        }
    }
}

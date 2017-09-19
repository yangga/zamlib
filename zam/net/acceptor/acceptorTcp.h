//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_ACCEPTORTCP_H
#define ZAMLIB_ACCEPTORTCP_H

#include <zam/base/exception.h>
#include "acceptor.h"

#include "../connection/connectionTcp.h"

#include <boost/bind.hpp>

namespace zam {
    namespace net {
        namespace acceptor {

            class acceptorTcp : public acceptor {
            public:
                struct Config {
                    std::string bindIp;
                    uint16_t bindPort;
                };

            public:
                explicit acceptorTcp(base::io::ioSystem &ios, warehouse::warehouse w, Config cfg)
                        : acceptor(ios, std::move(w))
                        , cfg_(std::move(cfg))
                        , acceptorSocket_(ios.getIos()) {}

                void startAccept() override {
                    using tcp = boost::asio::ip::tcp;

                    tcp::resolver resolver(ios().getIos());

                    std::string ipAddr(cfg_.bindIp);
                    if (ipAddr.empty()) {
                        ipAddr = "0.0.0.0";
                    }
                    auto port = std::to_string(cfg_.bindPort);

                    boost::system::error_code ec;

                    tcp::resolver::query query(ipAddr, port);
                    tcp::endpoint endpoint = *resolver.resolve(query, ec);

                    acceptorSocket_.open(endpoint.protocol(), ec);

                    acceptorSocket_.set_option(tcp::no_delay(true));
                    acceptorSocket_.set_option(tcp::acceptor::reuse_address(true));
                    acceptorSocket_.set_option(boost::asio::socket_base::linger(true, 0));
                    acceptorSocket_.bind(endpoint, ec);

                    if (ec) {
                        throw base::zamException(netError::failed_bind, ec.message());
                    }

                    acceptorSocket_.listen(boost::asio::socket_base::max_connections, ec);
                    if (ec) {
                        throw base::zamException(netError::failed_listen, ec.message());
                    }

                    startAcceptInternal();
                }

            private:
                void accept_handler(const boost::system::error_code &ec) {
                    if (!ec) {
                        conn_->eventHandler()->onAccept(conn_);

                        startAcceptInternal();
                    }
                }

                void startAcceptInternal() {
                    auto c = new connection::connectionTcp(ios());
                    c->active(this->warehouse());
                    conn_.reset(c);

                    acceptorSocket_.async_accept(c->socket(), strand().wrap(
                            boost::bind(&acceptorTcp::accept_handler, this, boost::asio::placeholders::error)));
                }

            private:
                Config cfg_;

                boost::asio::ip::tcp::acceptor acceptorSocket_;

                boost::shared_ptr<connection::connection> conn_;
            };
        }
    }
}

#endif //ZAMLIB_ACCEPTORTCP_H

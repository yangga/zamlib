//
// Created by SungWoo Yang on 2017. 9. 21..
//

#include "acceptorTcp.h"

#include "../connection/connectionTcp.h"

namespace zam {
    namespace net {
        namespace acceptor {

            acceptorTcp::acceptorTcp(base::io::ioSystem &ios, warehouse::warehouse w, Config cfg)
            : acceptor(ios, std::move(w))
            , cfg_(std::move(cfg))
            , acceptorSocket_(ios.getIos())
            {}

            void acceptorTcp::startAccept() {
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

                if (ec)
                    throw base::zamException(netError::failed_get_endpoint, ec.message());

                acceptorSocket_.set_option(tcp::no_delay(true));
                acceptorSocket_.set_option(tcp::acceptor::reuse_address(true));
                acceptorSocket_.set_option(boost::asio::socket_base::linger(true, 0));
                acceptorSocket_.bind(endpoint, ec);

                if (!!ec) {
                    throw base::zamException(netError::failed_bind, ec.message());
                }

                acceptorSocket_.listen(boost::asio::socket_base::max_connections, ec);
                if (!!ec) {
                    throw base::zamException(netError::failed_listen, ec.message());
                }

                startAcceptInternal();
            }

            void acceptorTcp::acceptHandler(const boost::system::error_code &ec) {
                if (!ec) {
                    conn_->startAccept();

                    conn_->ioPost(boost::bind(&handler::eventHandler::onAccept, conn_->eventHandler(), conn_));

                    startAcceptInternal();
                }
            }

            void acceptorTcp::startAcceptInternal() {
                connection::connectionTcp::Config cfg;
                cfg.keepAliveTimeMs = cfg_.keepAliveTimeMs;
                auto c = new connection::connectionTcp(ios(), std::move(cfg));
                c->initialize(this->warehouse());
                conn_.reset(c);

                acceptorSocket_.async_accept(c->socket(), strand().wrap(
                        boost::bind(&acceptorTcp::acceptHandler, this, boost::asio::placeholders::error)));
            }

        }
    }
}

//
// Created by SungWoo Yang on 2017. 9. 21..
//

#include "connectorTcp.h"

#include "../connection/connectionTcp.h"

#include <zam/base/exception.h>
#include <zam/base/logger.h>

namespace zam {
    namespace net {
        namespace connector {

            connectorTcp::connectorTcp(base::io::ioSystem& ios, warehouse::warehouse w, Config cfg)
            : connector(ios, std::move(w))
            , cfg_(std::move(cfg))
            {

            }

            connection_ptr_t connectorTcp::connect() {
                auto c = createConnection();

                c->toChild<connection::connectionTcp>().socket().connect(getEndpoint());
                c->startConnect();
                c->eventHandler()->onConnect(c);

                return c;
            }

            void connectorTcp::assignConnections(size_t connectionCnt) {
                if (0 == connectionCnt)
                    throw std::invalid_argument("connectionCnt must be bigger than 0");

                assignAsyncConnection(connectionCnt);
            }

            void connectorTcp::assignAsyncConnection(size_t remainCount) {
                if (0 >= remainCount)
                    return;

                try{
                    auto c = createConnection();
                    auto const ep = getEndpoint();

                    c->toChild<connection::connectionTcp>().socket().async_connect(
                            ep
                            , strand().wrap(boost::bind(
                                    &connectorTcp::connectHandler, this
                                    , boost::asio::placeholders::error, ep, c, remainCount - 1)));

                }//try
                catch (std::exception& e)
                {
                    ZAM_LOGE("default") << "connection failed. Exception: " << e.what();
                }
            }

            connection_ptr_t connectorTcp::createConnection()
            {
                using TCP = boost::asio::ip::tcp;

                auto c = new connection::connectionTcp(ios());
                c->initialize(this->warehouse());

                auto& s = c->socket();
                s.open(getEndpoint().protocol());

                return connection_ptr_t(c);
            }

            boost::asio::ip::tcp::endpoint
            connectorTcp::getEndpoint() {
                using tcp = boost::asio::ip::tcp;

                tcp::resolver resolver(ios().getIos());

                std::string ipAddr(cfg_.remoteIp);

                auto port = std::to_string(cfg_.remotePort);

                boost::system::error_code ec;

                tcp::resolver::query query(ipAddr, port);
                auto ep = *resolver.resolve(query, ec);

                if (ec) {
                    ZAM_LOGE("default") << "failed get endpoint. msg:" << ec.message();
                    throw base::zamException(netError::failed_get_endpoint, ec.message());
                }

                return ep;
            }

            bool connectorTcp::connectHandler(const boost::system::error_code& ec
                    , boost::asio::ip::tcp::endpoint ep
                    , connection_ptr_t conn
                    , size_t remainCnt) {

                if (!conn->toChild<connection::connectionTcp>().socket().is_open()){
                    ZAM_LOGE("default") << "connectorTcp::connectHandler - Connect timed out, ep:" << ep;
                    conn->toChild<connection::connectionTcp>().socket().close();
                    conn->eventHandler()->onConnectFailed(conn);
                    return false;
                }

                if (ec)
                {
                    ZAM_LOGE("default") << "connectorTcp::connectHandler - Connect error"
                                        << ", msg:" << ec.message()
                                        << ", ep:" << ep;
                    conn->toChild<connection::connectionTcp>().socket().close();
                    conn->eventHandler()->onConnectFailed(conn);
                    return false;
                }

                conn->startConnect();
                conn->eventHandler()->onConnect(conn);

                if (0 < remainCnt)
                    assignAsyncConnection(remainCnt);

                return true;
            }
        }
    }
}



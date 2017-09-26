//
// Created by SungWoo Yang on 2017. 9. 21..
//

#ifndef ZAMLIB_CONNECTORTCP_H
#define ZAMLIB_CONNECTORTCP_H

#include <zam/net/net.h>

#include "connector.h"

namespace zam {
    namespace net {
        namespace connector {

            class connectorTcp : public connector
            {
            public:
                struct Config {
                    std::string remoteIp;
                    uint16_t remotePort;
                    size_t keepAliveTimeMs = 0;
                };

                ZAMNET_API explicit connectorTcp(base::io::ioSystem& ios, warehouse::warehouse w, Config cfg);

                /// throw an exception when failed
                ZAMNET_API connection_ptr_t connect() override;

                /// throw an exception when failed
                ZAMNET_API void assignConnections(size_t connectionCnt) override;

                Config const& getConfig() const { return cfg_; }

            private:
                void assignAsyncConnection(size_t remainCount);

                connection_ptr_t createConnection();

                boost::asio::ip::tcp::endpoint getEndpoint();

                bool connectHandler(const boost::system::error_code& ec
                        , boost::asio::ip::tcp::endpoint ep
                        , connection_ptr_t conn
                        , size_t remainCnt);

            private:
                Config cfg_;
            };

        }
    }
}

#endif //ZAMLIB_CONNECTORTCP_H

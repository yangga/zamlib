//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_ACCEPTORTCP_H
#define ZAMLIB_ACCEPTORTCP_H

#include <zam/base/exception.h>
#include "acceptor.h"

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
                ZAMNET_API explicit acceptorTcp(base::io::ioSystem &ios, warehouse::warehouse w, Config cfg);

                ZAMNET_API void startAccept() override;

            private:
                void acceptHandler(const boost::system::error_code &ec);

                void startAcceptInternal();

            private:
                Config cfg_;

                boost::asio::ip::tcp::acceptor acceptorSocket_;

                boost::shared_ptr<connection::connection> conn_;
            };
        }
    }
}

#endif //ZAMLIB_ACCEPTORTCP_H

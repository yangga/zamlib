//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_CONNECTIONTCP_H
#define ZAMLIB_CONNECTIONTCP_H

#include <zam/net/net.h>

#include "connectionIO.h"

#include <zam/base/memory/pool.h>

namespace zam {
    namespace net {
        namespace connection {
            class connectionTcp
                    : public connectionIO
                            , public base::memory::pool<connectionTcp>
            {
            public:
                ZAMNET_API explicit connectionTcp(base::io::ioSystem& ios);

                endPoint remote_endpoint() override {
                    return endPoint{ sock_.remote_endpoint().address().to_string(), sock_.remote_endpoint().port() };
                }

            public:
                boost::asio::ip::tcp::socket& socket() { return sock_; }

            private:
                boost::asio::ip::tcp::socket sock_;
            };

        }


    }
}




#endif //ZAMLIB_CONNECTIONTCP_H

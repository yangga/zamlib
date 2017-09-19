//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_CONNECTIONTCP_H
#define ZAMLIB_CONNECTIONTCP_H

#include <zam/net/net.h>

#include "connection.h"

#include <zam/base/memory/pool.h>

namespace zam {
    namespace net {
        namespace connection {
            class connectionTcp
                : public connection
                , public base::memory::pool<connectionTcp>
            {
            public:
                ZAMNET_API explicit connectionTcp(base::io::ioSystem& ios);

                endPoint remote_endpoint() override;

                void startAccept() override;

            public:
                boost::asio::ip::tcp::socket& socket() { return sock_; }

            private:
                void startRead();
                void readHandler(const boost::system::error_code& ec, size_t bytes_transferred);

                void closing(boost::asio::socket_base::shutdown_type what);
                void close();

            private:
                boost::asio::ip::tcp::socket sock_;
                message msg_;
                size_t offset_;
                status status_;
            };

        }


    }
}




#endif //ZAMLIB_CONNECTIONTCP_H

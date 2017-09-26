//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_CONNECTIONTCP_H
#define ZAMLIB_CONNECTIONTCP_H

#include <zam/net/net.h>

#include "connection.h"
#include "../message/message.h"

#include <zam/base/memory/pool.h>

#include <boost/tuple/tuple.hpp>

namespace zam {
    namespace net {
        namespace connection {
            class connectionTcp
                : public connection
                , public base::memory::pool<connectionTcp>
            {
            public:
                struct Config {
                    size_t keepAliveTimeMs = 0;
                };

                ZAMNET_API explicit connectionTcp(base::io::ioSystem& ios, Config cfg);

                ZAMNET_API endPoint remote_endpoint() override;

                ZAMNET_API void startAccept() override;

                ZAMNET_API void startConnect() override;

                ZAMNET_API void closing() override;

                ZAMNET_API void send(message& msg, size_t msg_len) override;
                ZAMNET_API void sendRaw(void* src, size_t src_len) override;

            public:
                boost::asio::ip::tcp::socket& socket() { return sock_; }

            private:
                void startRead();
                void readHandler(const boost::system::error_code& ec, size_t bytes_transferred);
                void writeHandler(const boost::system::error_code& ec, size_t bytes_transferred);

                void closing(boost::asio::socket_base::shutdown_type what);
                void close();

                void renewExpireTime();
                void onExpireTime();

            private:
                Config cfg_;
                boost::asio::ip::tcp::socket sock_;
                message msg_;
                size_t offset_;
                status status_;
            };

        }


    }
}




#endif //ZAMLIB_CONNECTIONTCP_H

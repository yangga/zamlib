//
// Created by SungWoo Yang on 2017. 9. 15..
//

#ifndef ZAMLIB_LOGGERUDPSERVER_H
#define ZAMLIB_LOGGERUDPSERVER_H

#include <zam/base/base.h>

#include <zam/base/log/loggerDefine.h>

#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

#include <array>

namespace zam {
    namespace base {
        namespace log {
            namespace server {

                class loggerUdpServer : boost::noncopyable
                {
                public:
                    using delegate_recv = boost::function<void(char*,size_t,const boost::asio::ip::udp::endpoint&)>;

                public:
                    ZAMBASE_API loggerUdpServer(boost::asio::io_service& ios
                            , uint16_t portListen
                            , delegate_recv deleRecv=coutRecvBufDelegator);

                    ZAMBASE_API void start_receive();

                private:
                    void handle_receive(const boost::system::error_code& ec, std::size_t bytes_transferred);

                private:
                    boost::asio::io_service& ios_;
                    boost::asio::ip::udp::socket sock_;

                    std::array<char, MAX_REMOTE_LOG_SIZE> bufRecv_;
                    boost::asio::ip::udp::endpoint endpointRecv_;

                    delegate_recv delegateRecv_;

                private:
                    ZAMBASE_API static void coutRecvBufDelegator(char* buf, size_t buf_len, const boost::asio::ip::udp::endpoint& epRecv);
                };

            }
        }
    }
}


#endif //ZAMLIB_LOGGERUDPSERVER_H

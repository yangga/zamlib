//
// Created by SungWoo Yang on 2017. 9. 15..
//

#include "loggerUdpServer.h"

namespace asio = boost::asio;

using udp = boost::asio::ip::udp;

namespace zam {
    namespace base {
        namespace log {
            namespace server {

                loggerUdpServer::loggerUdpServer(base::io::ioSystem& ios
                        , uint16_t portListen
                        , delegate_recv deleRecv
                )
                : sock_(ios.getIos(), udp::endpoint(udp::v4(), portListen))
                , delegateRecv_(deleRecv)
                {
                }

                void loggerUdpServer::start_receive() {
                    sock_.async_receive_from(asio::buffer(bufRecv_), endpointRecv_,
                                              [this](boost::system::error_code ec, std::size_t bytes_recv){ this->handle_receive(ec, bytes_recv); });
                }

                void loggerUdpServer::handle_receive(const boost::system::error_code& ec, std::size_t bytes_transferred) {
                    if (!ec) {
                        try {
                            delegateRecv_(bufRecv_.data(), bytes_transferred, endpointRecv_);
                        } catch(...) {}
                    }

                    start_receive();
                }

                void loggerUdpServer::coutRecvBufDelegator(char* buf, size_t buf_len, const boost::asio::ip::udp::endpoint& epRecv) {
                    std::cout << "loggerUdpServer recved - " << buf << std::endl;
                }
            }
        }
    }
}
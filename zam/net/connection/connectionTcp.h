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

        class connectionTcp
                : public connectionIO
                , public base::memory::pool<connectionTcp>
        {
        public:
            explicit connectionTcp(base::io::ioSystem& ios);

            boost::asio::ip::tcp::socket& socket() { return sock_; }

        private:
            boost::asio::ip::tcp::socket sock_;
        };

    }
}




#endif //ZAMLIB_CONNECTIONTCP_H

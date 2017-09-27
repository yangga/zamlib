//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_ENDPOINT_H
#define ZAMLIB_ENDPOINT_H

#include <zam/net/net.h>

#include <string>
#include <sstream>

namespace zam {
    namespace net {
        namespace connection {

            struct endPoint
            {
                std::string address;
                uint16_t port;
            };

            ZAMNET_API std::string to_string(const endPoint& e);
        }
    }
}

#endif //ZAMLIB_ENDPOINT_H

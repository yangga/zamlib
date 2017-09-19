//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_ENDPOINT_H
#define ZAMLIB_ENDPOINT_H

#include <string>

namespace zam {
    namespace net {
        namespace connection {

            struct endPoint
            {
                std::string address;
                uint16_t port;
            };

        }
    }
}

#endif //ZAMLIB_ENDPOINT_H

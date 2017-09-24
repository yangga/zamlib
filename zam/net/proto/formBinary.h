//
// Created by SungWoo Yang on 2017. 9. 24..
//

#ifndef ZAMLIB_PROTO_FORM_BINARY_H
#define ZAMLIB_PROTO_FORM_BINARY_H

#include <zam/net/net.h>

#include "../message/messageOStream.h"

namespace zam {
    namespace net {
        namespace proto {

            struct formBinary {
                template <class PROTO_DATA_T>
                static constexpr bool check_value() { return true; }

                template <class PROTO_DATA_T>
                static void write(zam::net::messageOStream& os, const PROTO_DATA_T& data) {
                    os.write((const char*)(&data), sizeof(data));
                }
            };

        }
    }
}


#endif //ZAMLIB_PROTO_FORM_BINARY_H

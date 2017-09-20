//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_CIPHER_H
#define ZAMLIB_CIPHER_H

#include "../message/message.h"
#include "../message/messageIStream.h"
#include "../message/messageOStream.h"

#include <boost/shared_ptr.hpp>

namespace zam {
    namespace net {
        namespace cipher {

            struct cipher {
                virtual ~cipher() = default;

                /// returns : length of out
                virtual size_t encrypt(message& out, messageOStream& os) = 0;

                /// returns : length of out
                virtual size_t decrypt(message& out, messageIStream& is) = 0;
            };

        }

        using cipher_ptr_t = boost::shared_ptr<cipher::cipher>;
    }
}

#endif //ZAMLIB_CIPHER_H

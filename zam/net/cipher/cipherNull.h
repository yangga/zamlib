//
// Created by yangga on 2017. 9. 19..
//

#ifndef ZAMLIB_CIPHERNULL_H
#define ZAMLIB_CIPHERNULL_H

#include <zam/net/net.h>

#include "cipher.h"

namespace zam {
    namespace net {
        namespace cipher {

            class cipherNull : public cipher
            {
            public:
                ZAMNET_API size_t encrypt(message& out, messageOStream& os) override;

                /// returns : length of out
                ZAMNET_API size_t decrypt(message& out, messageIStream& is) override;
            };

        }
    }
}




#endif //ZAMLIB_CIPHERNULL_H

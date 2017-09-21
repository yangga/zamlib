//
// Created by yangga on 2017. 9. 19..
//

#include "cipherNull.h"

namespace zam {
    namespace net {
        namespace cipher {

            ZAMNET_API size_t cipherNull::encrypt(message& out, messageOStream& os) {
                out.swap(os.buf());
                return os.dataSize();
            }

            ZAMNET_API size_t cipherNull::decrypt(message& out, messageIStream& is) {
                out.swap(is.buf());
                return is.dataSize();
            }

        }
    }
}

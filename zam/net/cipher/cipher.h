//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_CIPHER_H
#define ZAMLIB_CIPHER_H

#include <boost/shared_ptr.hpp>

namespace zam {
    namespace net {
        namespace cipher {

            struct cipher {

            };

        }

        using cipher_ptr_t = boost::shared_ptr<cipher::cipher>;
    }
}

#endif //ZAMLIB_CIPHER_H

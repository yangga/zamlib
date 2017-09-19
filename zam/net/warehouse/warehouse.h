//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_WAREHOUSE_H
#define ZAMLIB_WAREHOUSE_H

#include "../cipher/cipher.h"
#include "../handler/eventHandler.h"
#include "../packer/packer.h"

#include <boost/function.hpp>
#include <boost/smart_ptr.hpp>

namespace zam {
    namespace net {
        namespace warehouse {

            struct warehouse
            {
                boost::function<cipher_ptr_t(void)> getCipher;
                boost::function<eventHandler_ptr_t(void)> getEventHandler;
                boost::function<packer_ptr_t(void)> getPacker;
            };

        }
    }
}

#endif //ZAMLIB_WAREHOUSE_H

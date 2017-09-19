//
// Created by yangga on 2017. 9. 18..
//

#ifndef ZAMLIB_PACKER_H
#define ZAMLIB_PACKER_H

#include "../message/message.h"

namespace zam {
    namespace net {
        namespace packer {

            struct packer {
                /// returns : length of out
                virtual size_t pack(message& out, message& in, size_t in_len) = 0;

                /// returns : length of out
                virtual size_t unpack(message& out, message& in, size_t in_len) = 0;
            };

        }

        using packer_ptr_t = boost::shared_ptr<packer::packer>;
    }
}

#endif //ZAMLIB_PACKER_H

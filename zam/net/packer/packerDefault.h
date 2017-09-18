//
// Created by yangga on 2017. 9. 18..
//

#ifndef ZAMLIB_PACKERDEFAULT_H
#define ZAMLIB_PACKERDEFAULT_H

#include "packer.h"

namespace zam {
    namespace net {
        namespace packer {

            class packerDefault : public packer {
            public:
                size_t pack(message& out, message& in, size_t in_len) override;
                size_t unpack(message& out, message& in, size_t in_len) override;
            };

        }
    }
}

#endif //ZAMLIB_PACKERDEFAULT_H

//
// Created by yangga on 2017. 9. 18..
//

#ifndef ZAMLIB_PACKERDEFAULT_H
#define ZAMLIB_PACKERDEFAULT_H

#include <zam/net/net.h>

#include "packer.h"

namespace zam {
    namespace net {
        namespace packer {

            class packerDefault : public packer {
            public:
                ZAMNET_API size_t pack(message& out, messageOStream& os) override;
                ZAMNET_API size_t unpack(message& out, messageIStream& is) override;
            };

        }
    }
}

#endif //ZAMLIB_PACKERDEFAULT_H

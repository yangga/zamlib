//
// Created by yangga on 2017. 9. 18..
//

#ifndef ZAMLIB_PACKER_H
#define ZAMLIB_PACKER_H

#include "../message/message.h"
#include "../message/messageIStream.h"
#include "../message/messageOStream.h"

#include <boost/shared_ptr.hpp>

namespace zam {
    namespace net {

        namespace packer {

            struct packer {
                virtual ~packer() = default;

                /// returns : length of out
                virtual size_t pack(message& out, messageIStream& is) = 0;

                /// returns : length of out
                virtual size_t unpack(message& out, messageIStream& is) = 0;
            };

        }

        using packer_ptr_t = boost::shared_ptr<packer::packer>;
    }
}

#endif //ZAMLIB_PACKER_H

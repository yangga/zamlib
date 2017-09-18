//
// Created by yangga on 2017. 9. 18..
//

#ifndef ZAMLIB_NETERROR_H
#define ZAMLIB_NETERROR_H

#include <zam/net/net.h>

namespace zam {
    namespace net {

        enum netError : int32_t
        {
            none = 0,

            overflow = 2000000,
            incompleted_packet = 2000001,
            invalid_packet = 2000002,
        };

    }
}

#endif //ZAMLIB_NETERROR_H

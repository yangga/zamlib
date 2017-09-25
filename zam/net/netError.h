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
            incompleted_packet,
            invalid_packet,
            failed_bind,
            failed_listen,
            failed_get_endpoint,
            invalid_protocol,
        };

    }
}

#endif //ZAMLIB_NETERROR_H

//
// Created by yangga on 2017. 9. 18..
//

#ifndef ZAMLIB_MESSAGE_H
#define ZAMLIB_MESSAGE_H

#include <zam/net/net.h>

#include <zam/base/buffer.h>
#include <zam/base/memory/pool.h>

namespace zam {
    namespace net {

        class message
            : public zam::base::buffer<ZAM_BUF_SIZE>
            , public zam::base::memory::pool<message>
        {

        };

    }
}




#endif //ZAMLIB_MESSAGE_H

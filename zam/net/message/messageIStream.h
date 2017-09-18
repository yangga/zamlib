//
// Created by yangga on 2017. 9. 18..
//

#ifndef ZAMLIB_MESSAGESTREAM_H
#define ZAMLIB_MESSAGESTREAM_H

#include <zam/net/net.h>

#include "message.h"

#include <zam/base/stream/streamInputBuf.h>

namespace zam {
    namespace net {

        class messageIStream
                : public zam::base::stream::streamInputBuf<message>
        {
        public:
            ZAMNET_API explicit messageIStream(message& m, size_t dataLen);
        };

    }
}




#endif //ZAMLIB_MESSAGESTREAM_H

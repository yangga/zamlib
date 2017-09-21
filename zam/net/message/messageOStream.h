//
// Created by yangga on 2017. 9. 18..
//

#ifndef ZAMLIB_MESSAGEOSTREAM_H
#define ZAMLIB_MESSAGEOSTREAM_H

#include <zam/net/net.h>

#include "message.h"

#include <zam/base/stream/streamOutputBuf.h>

namespace zam {
    namespace net {

        class messageOStream
        : public zam::base::stream::streamOutputBuf<message>
        {
        public:
            ZAMNET_API explicit messageOStream(message& m, size_t offset=0);
        };

    }
}

#endif //ZAMLIB_MESSAGEOSTREAM_H

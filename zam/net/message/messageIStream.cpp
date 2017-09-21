//
// Created by yangga on 2017. 9. 18..
//

#include "messageIStream.h"

namespace zam {
    namespace net {

        messageIStream::messageIStream(message& m, size_t dataLen)
        : zam::base::stream::streamInputBuf<message>(m, dataLen)
        {
        }

    }
}

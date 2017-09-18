//
// Created by yangga on 2017. 9. 18..
//

#include "messageOStream.h"

namespace zam {
    namespace net {

        messageOStream::messageOStream(message& m)
                : zam::base::stream::streamOutputBuf<message>(m)
        {
        }

    }
}

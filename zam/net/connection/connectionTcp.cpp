//
// Created by SungWoo Yang on 2017. 9. 19..
//

#include "connectionTcp.h"

namespace zam {
    namespace net {

        connectionTcp::connectionTcp(base::io::ioSystem& ios)
        : connectionIO(ios)
        , sock_(ios.getIos())
        {}

    }
}

//
// Created by SungWoo Yang on 2017. 9. 17..
//

#ifndef ZAMLIB_ACCEPTOR_H
#define ZAMLIB_ACCEPTOR_H

#include <zam/net/net.h>

namespace zam {
    namespace net {

        class ZAMNET_API acceptor {
        public:
            acceptor(base::io::ioSystem& ios);
        };

    }
}

#endif //ZAMLIB_ACCEPTOR_H

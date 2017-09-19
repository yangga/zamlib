//
// Created by SungWoo Yang on 2017. 9. 17..
//

#ifndef ZAMLIB_ACCEPTOR_H
#define ZAMLIB_ACCEPTOR_H

#include <zam/net/net.h>

#include <zam/base/io/ioObject.h>

namespace zam {
    namespace net {

        class acceptor : public base::io::ioObject {
        protected:
            explicit acceptor(base::io::ioSystem& ios) : base::io::ioObject(ios) {}

        public:
            virtual void startAccept() = 0;
        };

    }
}

#endif //ZAMLIB_ACCEPTOR_H

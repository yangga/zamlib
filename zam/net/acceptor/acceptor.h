//
// Created by SungWoo Yang on 2017. 9. 17..
//

#ifndef ZAMLIB_ACCEPTOR_H
#define ZAMLIB_ACCEPTOR_H

#include <zam/net/net.h>

#include "../warehouse/warehouse.h"

#include <zam/base/io/ioObject.h>

namespace zam {
    namespace net {
        namespace acceptor {

            class acceptor : public base::io::ioObject {
            protected:
                explicit acceptor(base::io::ioSystem& ios, warehouse::warehouse w)
                        : base::io::ioObject(ios)
                        , warehouse_(std::move(w))
                {}

            public:
                virtual void startAccept() = 0;

                warehouse::warehouse& warehouse() { return warehouse_; }

            private:
                warehouse::warehouse warehouse_;
            };

        }
    }
}

#endif //ZAMLIB_ACCEPTOR_H

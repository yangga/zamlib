//
// Created by SungWoo Yang on 2017. 9. 21..
//

#ifndef ZAMLIB_CONNECTOR_H
#define ZAMLIB_CONNECTOR_H

#include <zam/net/net.h>

#include "../connection/connection.h"
#include "../warehouse/warehouse.h"

#include <zam/base/io/ioObject.h>

namespace zam {
    namespace net {
        namespace connector {

            struct connector : public base::io::ioObject
            {
            protected:
                explicit connector(base::io::ioSystem& ios, warehouse::warehouse w)
                : base::io::ioObject(ios)
                , warehouse_(std::move(w))
                {
                    assert(warehouse_.getPacker);
                    assert(warehouse_.getCipher);
                    assert(warehouse_.getEventHandler);
                }

            public:
                virtual connection_ptr_t connect() = 0;
                virtual void assignConnections(size_t connectionCnt) = 0;

                warehouse::warehouse& warehouse() { return warehouse_; }

            private:
                warehouse::warehouse warehouse_;
            };

        }
    }
}

#endif //ZAMLIB_CONNECTOR_H

//
// Created by yangga on 2017. 9. 23..
//

#include "connection.h"

namespace zam {
    namespace net {
        namespace connection {

            connection::connection(base::io::ioSystem& ios) : base::io::ioObject(ios)
            {}

            void connection::initialize(warehouse::warehouse& wh) {
                cipher_     = wh.getCipher();
                evtHandler_ = wh.getEventHandler();
                packer_     = wh.getPacker();

                if (evtHandler_)
                    evtHandler_->onInitHandler();
            }

        }
    }
}

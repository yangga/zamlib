//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_CONNECTION_H
#define ZAMLIB_CONNECTION_H

#include "endPoint.h"

#include "../warehouse/warehouse.h"

#include <boost/enable_shared_from_this.hpp>

namespace zam {
    namespace net {
        namespace connection {
            struct connection
                    : public boost::enable_shared_from_this<connection>
            {
            public:
                virtual endPoint remote_endpoint() = 0;

            public:
                void active(warehouse::warehouse& wh) {
                    cipher_     = wh.getCipher();
                    evtHandler_ = wh.getEventHandler();
                    packer_     = wh.getPacker();
                }

                cipher_ptr_t& cipher() { return cipher_; }
                eventHandler_ptr_t& eventHandler() { return evtHandler_; }
                packer_ptr_t& packer() { return packer_; }

            private:
                cipher_ptr_t cipher_;
                eventHandler_ptr_t evtHandler_;
                packer_ptr_t packer_;
            };
        }
    }
}

#endif //ZAMLIB_CONNECTION_H

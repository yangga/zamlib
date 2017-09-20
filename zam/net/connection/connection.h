//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_CONNECTION_H
#define ZAMLIB_CONNECTION_H

#include "endPoint.h"

#include "../warehouse/warehouse.h"

#include <zam/base/io/ioObject.h>

#include <boost/enable_shared_from_this.hpp>

namespace zam {
    namespace net {

        namespace connection {
            class connection
                : public base::io::ioObject
                , public boost::enable_shared_from_this<connection>
            {
            public:
                enum class status : unsigned char {
                    open = 0,
                    closing = 1,
                    close = 2,
                };

                virtual endPoint remote_endpoint() = 0;
                virtual void startAccept() = 0;
                virtual void closing() = 0;

            public:
                void initialize(warehouse::warehouse& wh) {
                    cipher_     = wh.getCipher();
                    evtHandler_ = wh.getEventHandler();
                    packer_     = wh.getPacker();
                }

                cipher_ptr_t& cipher() { return cipher_; }
                eventHandler_ptr_t& eventHandler() { return evtHandler_; }
                packer_ptr_t& packer() { return packer_; }

                template <class CHILD_CONNECTION>
                CHILD_CONNECTION& toChild() {
                    static_assert(std::is_base_of<connection, CHILD_CONNECTION>::value, "child connection must be child of connection");
                    return dynamic_cast<CHILD_CONNECTION&>(*this);
                }

            protected:
                explicit connection(base::io::ioSystem& ios) : base::io::ioObject(ios)
                {}

            private:
                cipher_ptr_t cipher_;
                eventHandler_ptr_t evtHandler_;
                packer_ptr_t packer_;
            };
        }
    }
}

#endif //ZAMLIB_CONNECTION_H

//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_IOOBJECT_H
#define ZAMLIB_IOOBJECT_H

#include <zam/base/base.h>

#include "ioSystem.h"

#include <boost/asio/strand.hpp>

namespace zam {
    namespace base {
        namespace io {

            class ioObject
            {
            public:
                virtual ~ioObject() = default;

                boost::asio::strand& strand() { return strand_; }

                ioSystem& ios() { return ios_; }

                template <typename CompletionHandler>
                BOOST_ASIO_INITFN_RESULT_TYPE(CompletionHandler, void ())
                ioDispatch(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler) {
                    return strand_.dispatch(handler);
                }

                template <typename CompletionHandler>
                BOOST_ASIO_INITFN_RESULT_TYPE(CompletionHandler, void ())
                ioPost(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler) {
                    return strand_.post(handler);
                }

            protected:
                ZAMBASE_API ioObject(ioObject& ioo);
                ZAMBASE_API explicit ioObject(ioSystem& ios);

            private:
                ioSystem& ios_;
                boost::asio::strand strand_;
            };

        }
    }
}

#endif //ZAMLIB_IOOBJECT_H

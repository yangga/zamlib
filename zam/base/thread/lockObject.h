//
// Created by SungWoo Yang on 2017. 9. 26..
//

#ifndef ZAMLIB_LOCKOBJECT_H
#define ZAMLIB_LOCKOBJECT_H

#include <zam/base/base.h>
#include <zam/base/macro.h>

#include <boost/function.hpp>
#include <boost/thread.hpp>

namespace zam {
    namespace base {
        namespace thread {

            template <typename OBJ_T, typename MUTEX_T=boost::mutex>
            class lockObject
            {
            public:
                using object_t = std::remove_const_t<std::remove_reference_t<OBJ_T>>;

                void lock(boost::function<void(object_t& obj)> fn) {
                    ZAM_LOCK(mx_);
                    fn(obj_);
                }

                void lock(boost::function<void(const object_t& obj)> fn) const {
                    ZAM_LOCK(mx_);
                    fn(obj_);
                }

            private:
                MUTEX_T mx_;
                object_t obj_;
            };

        }
    }
}

#endif //ZAMLIB_LOCKOBJECT_H

//
// Created by yangga on 2017. 9. 18..
//

#ifndef ZAMLIB_POOL_H
#define ZAMLIB_POOL_H

#include <zam/base/base.h>

#include <boost/pool/pool.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

namespace zam {
    namespace base {
        namespace memory {

            template< typename __classname, typename __mutexname=boost::mutex >
            class pool
            {
            public:
                static void* operator new(size_t size) {
                    boost::lock_guard<__mutexname> lock(mutex_);
                    return static_cast<__classname*>(thisPool_.malloc());
                }

                static void operator delete(void* ptr, size_t size) {
                    boost::lock_guard<__mutexname> lock(mutex_);
                    thisPool_.free(ptr);
                }
                static void destruct(__classname* ptr){
                    delete ptr;
                }

            private:
                static boost::pool<> thisPool_;
                static __mutexname mutex_;
            };

            template< typename __classname, typename __mutexname >
            boost::pool<> pool<__classname, __mutexname>::thisPool_(sizeof(__classname));

            template< typename __classname, typename __mutexname >
            __mutexname pool<__classname, __mutexname>::mutex_;

        }
    }
}

#endif //ZAMLIB_POOL_H

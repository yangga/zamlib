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
            class memory_pool
            {
            public:
                static void* operator new(size_t size) {
                    boost::lock_guard<__mutexname> lock(_mutex);
                    return static_cast<__classname*>(_thisPool.malloc());
                }

                static void operator delete(void* ptr, size_t size) {
                    boost::lock_guard<__mutexname> lock(_mutex);
                    _thisPool.free(ptr);
                }
                static void destruct(__classname* ptr){
                    delete ptr;
                }

            private:
                static boost::pool<> _thisPool;
                static __mutexname _mutex;
            };

            template< typename __classname, typename __mutexname >
            boost::pool<> memory_pool<__classname, __mutexname>::_thisPool(sizeof(__classname));

            template< typename __classname, typename __mutexname >
            __mutexname memory_pool<__classname, __mutexname>::_mutex;

        }
    }
}

#endif //ZAMLIB_POOL_H

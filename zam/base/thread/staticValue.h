//
// Created by yangga on 2017. 9. 18..
//

#ifndef ZAMLIB_STATICVALUE_H
#define ZAMLIB_STATICVALUE_H

#include <boost/thread/tss.hpp>

#include <type_traits>

namespace zam {
    namespace base {
        namespace thread {

            template <typename T
                    , int IDENTIFIER>
            class staticValue
            {
            public:
                using type_t = T;

                static constexpr int identifier_v = IDENTIFIER;

            public:
                static T& get()
                {
                    static boost::thread_specific_ptr<T> threadValue;
                    if (nullptr == threadValue.get()){
                        threadValue.reset(new T());
                    }
                    return *threadValue;
                }
            };

        }
    }
}

#endif //ZAMLIB_STATICVALUE_H

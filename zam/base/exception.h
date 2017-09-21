//
// Created by yangga on 2017. 9. 18..
//

#ifndef ZAMLIB_EXCEPTION_H
#define ZAMLIB_EXCEPTION_H

#include <zam/base/base.h>

namespace zam {
    namespace base {

        class zamException : public std::runtime_error
        {
        public:
            zamException(int errNo, const std::string& msg) : std::runtime_error(msg), errNo_(errNo) {}
            zamException(int errNo, const char* msg) : std::runtime_error(msg), errNo_(errNo) {}
            virtual ~zamException() = default;

            int errorNo() const { return errNo_; }

        protected:
            const int errNo_;
        };

    }
}

#endif //ZAMLIB_EXCEPTION_H

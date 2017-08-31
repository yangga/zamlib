//
// Created by SungWoo Yang on 2017. 8. 30..
//

#ifndef ZAM_LOG_H
#define ZAM_LOG_H

#include "loggerDefine.h"

namespace zam {
    namespace base {
        namespace log {

            class logger {
            public:
                logger() = delete;
                logger(const char* tag, level lv);
                ~logger() = default;

                template <typename T>
                logger& operator << (T const& v) {
                    return *this;
                }
            };



        }   // namespace log
    }   // namespace base
}  // namespace zam


#endif //ZAM_LOG_H

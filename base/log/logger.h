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
                void trace(const char* fmt, ...);
                void debug(const char* fmt, ...);
                void info(const char* fmt, ...);
                void warn(const char* fmt, ...);
                void error(const char* fmt, ...);
                void fatal(const char* fmt, ...);

                inline bool checkLevel(level lv) const;

            private:
                void log(level lv, const char* txt);

            private:
                level level_;
            };

        }   // namespace log
    }   // namespace base
}  // namespace zam


#endif //ZAM_LOG_H

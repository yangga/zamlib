//
// Created by SungWoo Yang on 2017. 8. 30..
//

#ifndef ZAM_BASE_LOG_LOGGERDEFINE_H
#define ZAM_BASE_LOG_LOGGERDEFINE_H

#include <string>

namespace zam {
    namespace base {
        namespace log {

            enum level : uint32_t {
                trace = 1 << 0,
                debug = 1 << 1,
                info = 1 << 2,
                warn = 1 << 3,
                error = 1 << 4,
                fatal = 1 << 5,

                all = trace|debug|info|warn|error|fatal
            };
            std::string toString(level lv);
            level toLevel(const char* names);

            enum streamType : uint32_t {
                none = 0,
                console = 1 << 0,
                file = 1 << 1,
                tracer = 1 << 2,
                udp = 1 << 3
            };

        }   // namespace log
    }   // namespace base
}  // namespace zam

#endif //ZAM_BASE_LOG_LOGGERDEFINE_H

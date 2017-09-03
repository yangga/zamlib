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
                all = 0,
                trace = 1,
                debug = 2,
                info = 3,
                warn = 4,
                error = 5,
                fatal = 6
            };
            std::string toString(level lv);
            level toLevel(const char* name);

            enum streamType : uint32_t {
                none = 0,
                console = 1 << 0,
                file = 1 << 1,
                tracer = 1 << 2,
                udp = 1 << 3
            };
            std::string toString(streamType type);
            streamType toStreamType(const char *name);

        }   // namespace log
    }   // namespace base
}  // namespace zam

#endif //ZAM_BASE_LOG_LOGGERDEFINE_H

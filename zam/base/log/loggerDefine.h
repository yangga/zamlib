//
// Created by SungWoo Yang on 2017. 8. 30..
//

#ifndef ZAM_BASE_LOG_LOGGERDEFINE_H
#define ZAM_BASE_LOG_LOGGERDEFINE_H

#include <zam/base/base.h>

#include <boost/log/expressions/keyword.hpp>

#include <string>

namespace zam {
    namespace base {
        namespace log {

            enum level : uint32_t {
                all = 0,
                trace = 0,
                debug,
                info,
                warn,
                error,
                fatal
            };
            BOOST_LOG_ATTRIBUTE_KEYWORD(zam_severity, "Severity", level);

            std::string toString(level lv);
            level toLevel(const char* name);
            std::ostream& operator << (std::ostream& strm, level lv);

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

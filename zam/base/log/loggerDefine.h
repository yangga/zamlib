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

            /// level
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

            ZAMBASE_API const char* toString(level lv);
            ZAMBASE_API level toLevel(const char* name);
            ZAMBASE_API std::ostream& operator << (std::ostream& strm, level lv);

            /// streamType
            enum streamType : uint32_t {
                console = 0,
                file,
                tracer,
                syslog,
                udp,

                count
            };
            ZAMBASE_API const char* toString(streamType type);
            ZAMBASE_API streamType toStreamType(const char *name);

            /// streamType
            enum formatType : uint32_t {
                plain = 0,
                xml = 1 << 0,
                json = 1 << 1
            };
            ZAMBASE_API const char* toString(formatType type);
            ZAMBASE_API formatType toFormatType(const char *name);

            /// udp
            constexpr unsigned int MAX_REMOTE_LOG_SIZE = 8192;


        }   // namespace log
    }   // namespace base
}  // namespace zam

#endif //ZAM_BASE_LOG_LOGGERDEFINE_H

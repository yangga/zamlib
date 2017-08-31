//
// Created by SungWoo Yang on 2017. 8. 30..
//

#ifndef ZAM_LOG_H
#define ZAM_LOG_H

namespace zam {
    namespace base {
        namespace log {

            class loggerConfig;

            class logger {

            public:
                static void allocate(const char* tag, loggerConfig const& cfg);

                static void trace(const char* tag, const char* fmt, ...);
                static void debug(const char* tag, const char* fmt, ...);
                static void info(const char* tag, const char* fmt, ...);
                static void warn(const char* tag, const char* fmt, ...);
                static void error(const char* tag, const char* fmt, ...);
                static void fatal(const char* tag, const char* fmt, ...);
            };

        }   // namespace log
    }   // namespace base
}  // namespace zam


#endif //ZAM_LOG_H

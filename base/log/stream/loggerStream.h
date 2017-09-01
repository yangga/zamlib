//
// Created by SungWoo Yang on 2017. 9. 1..
//

#ifndef ZAM_BASE_LOG_LOGGERSTREAM_H
#define ZAM_BASE_LOG_LOGGERSTREAM_H

namespace zam {
    namespace base {
        namespace log {

            class loggerStream {
            public:
                virtual void write(const char*) = 0;
            };

        }
    }
}

#endif //ZAM_BASE_LOG_LOGGERSTREAM_H

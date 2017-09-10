//
// Created by SungWoo Yang on 2017. 9. 1..
//

#ifndef ZAM_BASE_LOG_LOGGERINITIALIZER_H
#define ZAM_BASE_LOG_LOGGERINITIALIZER_H

#include <zam/base/base.h>
#include <zam/base/log/loggerDefine.h>

namespace zam {
    namespace base {
        namespace log {

            class logger;

            class ZAMBASE_API loggerInitializer {
            public:
                static logger& initializeLogger(logger& lg, const char* tag, level lv);
            };

        }
    }
}


#endif //ZAM_BASE_LOG_LOGGERINITIALIZER_H

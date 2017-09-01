//
// Created by SungWoo Yang on 2017. 9. 1..
//

#ifndef ZAM_LOGGERINITIALIZER_H
#define ZAM_LOGGERINITIALIZER_H

#include "loggerDefine.h"

namespace zam {
    namespace base {
        namespace log {

            class logger;

            class loggerInitializer {
            public:
                static logger& initializeLogger(logger& lg, const char* tag, level lv);
            };

        }
    }
}


#endif //ZAM_LOGGERINITIALIZER_H

//
// Created by SungWoo Yang on 2017. 8. 31..
//

#ifndef ZAM_LOGGERMANAGER_H
#define ZAM_LOGGERMANAGER_H

#include "loggerConfig.h"

namespace zam {
    namespace base {
        namespace log {

            class loggerManager {
                static void allocate(const char* tag, loggerConfig const& cfg);
            };
        }
    }
}


#endif //ZAM_LOGGERMANAGER_H

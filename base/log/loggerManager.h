//
// Created by SungWoo Yang on 2017. 8. 31..
//

#ifndef ZAM_BASE_LOG_LOGGERMANAGER_H
#define ZAM_BASE_LOG_LOGGERMANAGER_H

namespace zam {
    namespace base {
        namespace log {

            class loggerConfig;

            class loggerManager {
                static void allocate(const char* tag, loggerConfig const& cfg);
            };
        }
    }
}


#endif //ZAM_BASE_LOG_LOGGERMANAGER_H

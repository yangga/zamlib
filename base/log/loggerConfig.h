//
// Created by SungWoo Yang on 2017. 8. 30..
//

#ifndef ZAM_BASE_LOG_LOGGERCONFIG_H
#define ZAM_BASE_LOG_LOGGERCONFIG_H

#include <json/value.h>

#include "loggerDefine.h"

namespace zam {
    namespace base {
        namespace log {

            struct loggerConfig {
                streamType type;
                level lv;
            };

            struct loggerConfigConsole : loggerConfig {

            };

            struct loggerConfigFile : loggerConfig {

            };

            struct loggerConfigTracer : loggerConfig {

            };

        }   // namespace log
    }   // namespace base
}  // namespace zam

#endif //ZAM_BASE_LOG_LOGGERCONFIG_H

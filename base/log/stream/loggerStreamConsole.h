//
// Created by SungWoo Yang on 2017. 9. 1..
//

#ifndef ZAM_BASE_LOG_LOGGERSTREAMCONSOLE_H
#define ZAM_BASE_LOG_LOGGERSTREAMCONSOLE_H

#include "loggerStream.h"

#include "../loggerConfig.h"

namespace zam {
    namespace base {
        namespace log {

            struct loggerConfigStreamConsole : loggerConfig {

            };

            class loggerStreamConsole
                    : public loggerStream {
            public:
                void write(const char* text) override;
            };

        }
    }
}


#endif //ZAM_BASE_LOG_LOGGERSTREAMCONSOLE_H

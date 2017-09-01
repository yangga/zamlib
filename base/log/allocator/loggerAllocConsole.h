//
// Created by SungWoo Yang on 2017. 9. 1..
//

#ifndef ZAM_LOGGERALLOCCONSOLE_H
#define ZAM_LOGGERALLOCCONSOLE_H

#include "loggerAlloc.h"

namespace zam {
    namespace base {
        namespace log {

            class loggerAllocConsole
                    : public loggerAlloc {
            public:
                void initialize(loggerConfig const& cfg) override;
            };

        }
    }
}


#endif //ZAM_LOGGERALLOCCONSOLE_H

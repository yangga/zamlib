//
// Created by SungWoo Yang on 2017. 9. 1..
//

#ifndef ZAM_LOGGERALLOC_H
#define ZAM_LOGGERALLOC_H

#include "../loggerDefine.h"
#include "../loggerConfig.h"

namespace zam {
    namespace base {
        namespace log {

            class loggerAlloc {
            public:
                virtual void initialize(loggerConfig const& cfg) = 0;
            };

        }
    }
}

#endif //ZAM_LOGGERALLOC_H

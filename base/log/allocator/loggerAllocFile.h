//
// Created by SungWoo Yang on 2017. 9. 1..
//

#ifndef ZAM_LOGGERALLOCFILE_H
#define ZAM_LOGGERALLOCFILE_H

#include "loggerAlloc.h"

namespace zam {
    namespace base {
        namespace log {

            class loggerAllocFile
                    : public loggerAlloc {
            public:
                void initialize(loggerConfig const& cfg) override;
            };

        }
    }
}


#endif //ZAM_LOGGERALLOCFILE_H

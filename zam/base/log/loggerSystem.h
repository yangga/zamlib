//
// Created by SungWoo Yang on 2017. 8. 31..
//

#ifndef ZAM_BASE_LOG_LOGGERSYSTEM_H
#define ZAM_BASE_LOG_LOGGERSYSTEM_H

#include <zam/base/base.h>

#include "loggerDefine.h"

#include <json/value.h>

namespace zam {
    namespace base {
        namespace log {

            class ZAMBASE_API loggerSystem {
            public:
                static void allocate(const char* tag, Json::Value const& vAppender);

                static void load(Json::Value const& vCfg);
                static void load(const char* filename);
            };
        }
    }
}


#endif //ZAM_BASE_LOG_LOGGERSYSTEM_H

//
// Created by SungWoo Yang on 2017. 8. 31..
//

#ifndef ZAM_BASE_LOG_LOGGERSYSTEM_H
#define ZAM_BASE_LOG_LOGGERSYSTEM_H

#include <json/value.h>

#include <unordered_map>

namespace zam {
    namespace base {
        namespace log {

            class loggerConfig;

            class loggerSystem {
            public:
                static void allocate(const char* tag, loggerConfig const& cfg);

                static void load(Json::Value const& vCfg);
                static void load(const char* filename);
            };
        }
    }
}


#endif //ZAM_BASE_LOG_LOGGERSYSTEM_H

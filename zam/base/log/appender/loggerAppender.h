//
// Created by SungWoo Yang on 2017. 9. 1..
//

#ifndef __ZAM_LOG_APPENDER_LOGGERAPPENDER_H__
#define __ZAM_LOG_APPENDER_LOGGERAPPENDER_H__

#include <zam/base/base.h>
#include <zam/base/log/loggerDefine.h>

#include <json/value.h>

namespace zam {
    namespace base {
        namespace log {

            class loggerWriter;

            class loggerAppender {
            public:
                virtual void load(loggerWriter &writer, Json::Value const &vAppender) = 0;
            };

        }
    }
}

#endif //__ZAM_LOG_APPENDER_LOGGERAPPENDER_H__

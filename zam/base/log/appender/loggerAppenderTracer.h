//
// Created by SungWoo Yang on 2017. 9. 2..
//

#ifndef __ZAM_LOG_APPENDER_LOGGERAPPENDER_TRACER_H__
#define __ZAM_LOG_APPENDER_LOGGERAPPENDER_TRACER_H__

#include <zam/base/base.h>

#include "loggerAppender.h"

namespace zam {
    namespace base {
        namespace log {

            class loggerAppenderTracer
                    : public loggerAppender {
            public:
                void load(loggerWriter &writer, Json::Value const &) override;
            };

        }
    }
}


#endif //__ZAM_LOG_APPENDER_LOGGERAPPENDER_TRACER_H__

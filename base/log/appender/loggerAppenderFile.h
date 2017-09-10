//
// Created by SungWoo Yang on 2017. 9. 1..
//

#ifndef __ZAM_LOG_APPENDER_LOGGERAPPENDER_FILE_H__
#define __ZAM_LOG_APPENDER_LOGGERAPPENDER_FILE_H__

#include "base/base.h"
#include "loggerAppender.h"

namespace zam {
    namespace base {
        namespace log {

            class ZAMBASE_API loggerAppenderFile
                    : public loggerAppender {
            public:
                void load(loggerWriter &writer, Json::Value const &) override;
            };

        }
    }
}


#endif //__ZAM_LOG_APPENDER_LOGGERAPPENDER_FILE_H__

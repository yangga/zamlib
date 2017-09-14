//
// Created by yangga on 2017. 9. 14..
//

#ifndef ZAMLIB_LOGGERAPPENDERSYSLOG_H
#define ZAMLIB_LOGGERAPPENDERSYSLOG_H

#include <zam/base/base.h>

#include "loggerAppender.h"

namespace zam {
    namespace base {
        namespace log {

            class loggerAppenderSyslog : public loggerAppender {
            public:
                void load(loggerWriter &writer, Json::Value const &vAppender) override;
            };

        }
    }
}


#endif //ZAMLIB_LOGGERAPPENDERSYSLOG_H

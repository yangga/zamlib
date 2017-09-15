//
// Created by SungWoo Yang on 2017. 9. 15..
//

#include "appenderPool.h"

#include "loggerAppenderConsole.h"
#include "loggerAppenderFile.h"
#include "loggerAppenderTracer.h"
#include "loggerAppenderSyslog.h"
#include "loggerAppenderUdp.h"

namespace zam {
    namespace base {
        namespace log {

            appenderPool::appenderPool() {
                appenders_[streamType::console] = new loggerAppenderConsole();
                appenders_[streamType::file]    = new loggerAppenderFile();
                appenders_[streamType::tracer]  = new loggerAppenderTracer();
                appenders_[streamType::syslog]  = new loggerAppenderSyslog();
                appenders_[streamType::udp]     = new loggerAppenderUdp();
            }

            loggerAppender* appenderPool::getAppender(streamType type) {
                return appenders_[type];
            }

        }
    }
}

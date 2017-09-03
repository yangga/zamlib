//
// Created by SungWoo Yang on 2017. 9. 1..
//

#include "base.h"
#include "loggerInitializer.h"

#include "loggerWriter.h"
#include "base/log/logger.h"

namespace zam {
    namespace base {
        namespace log {

            loggerWriter g_writer("default");
            logger& loggerInitializer::initializeLogger(logger& lg, const char* tag, level lv) {
                lg.writer_ = &g_writer;
                lg.lv_ = lv;
                return lg;
            }

        }
    }
}

//
// Created by SungWoo Yang on 2017. 9. 1..
//

#include "base.h"
#include "loggerInitializer.h"

#include "logWriter.h"
#include "base/log/logger.h"

namespace zam {
    namespace base {
        namespace log {

            logWriter g_writer;
            logger& loggerInitializer::initializeLogger(logger& lg, const char* tag, level lv) {
                lg.writer_ = &g_writer;
                lg.lv_ = lv;
                return lg;
            }

        }
    }
}

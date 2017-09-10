//
// Created by SungWoo Yang on 2017. 9. 1..
//

#include "loggerInitializer.h"

#include "loggerPool.h"
#include "loggerWriter.h"

#include "base/log/logger.h"

namespace zam {
    namespace base {
        namespace log {

            logger& loggerInitializer::initializeLogger(logger& lg, const char* tag, level lv) {
                lg.writer_ = loggerPool::instance().get(tag);
                assert(nullptr != lg.writer_);

                lg.lv_ = lv;
                return lg;
            }

        }
    }
}

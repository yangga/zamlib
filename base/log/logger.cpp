//
// Created by SungWoo Yang on 2017. 8. 30..
//

#include "base.h"
#include "logger.h"

#include <iostream>

#include "loggerDefine.h"
#include "base/log/detail/loggerWriter.h"

namespace zam {
    namespace base {
        namespace log {

            logger::~logger() {
                if (writer_ && writer_->checkLevel(lv_))
                    flush();
            }

            void logger::flush() {
                writer_->flush(lv_, ss_.str().c_str());
            }

        }
    }
}
//
// Created by SungWoo Yang on 2017. 9. 20..
//

#include "logger.h"

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
//
// Created by SungWoo Yang on 2017. 8. 30..
//

#include "base.h"
#include "logger.h"

#include <iostream>

#include "loggerDefine.h"
#include "loggerConfig.h"


namespace zam {
    namespace base {
        namespace log {

            logger::~logger() {
                flush();
            }

            void logger::flush() {
                writer_->flush(ss_.str().c_str());
            }

        }
    }
}
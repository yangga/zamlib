//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include "base.h"
#include "loggerWriter.h"

#include <iostream>

namespace zam {
    namespace base {
        namespace log {

            loggerWriter::loggerWriter(std::string name)
                : name_(std::move(name))
            {
            }

            void loggerWriter::flush(const char* txt) {
                std::cout << txt << std::endl;
            }

        }
    }
}

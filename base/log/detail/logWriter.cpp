//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include "base.h"
#include "logWriter.h"

#include <iostream>

namespace zam {
    namespace base {
        namespace log {

            void logWriter::flush(const char* txt) {
                std::cout << txt << std::endl;
            }

        }
    }
}

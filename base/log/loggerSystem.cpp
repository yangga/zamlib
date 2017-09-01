//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include "base.h"
#include "loggerSystem.h"

#include "allocator/loggerAllocConsole.h"
#include "allocator/loggerAllocFile.h"

namespace zam {
    namespace base {
        namespace log {

            struct {
                streamType type;
                loggerAlloc* allocator;
            } __log_allocators__[] = {
                    { streamType::console, new loggerAllocConsole },
                    { streamType::file, new loggerAllocFile }
            };


            void loggerSystem::allocate(const char* tag, loggerConfig const& cfg) {

            }

        }
    }
}

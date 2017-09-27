//
// Created by SungWoo Yang on 2017. 9. 27..
//

#include "loggerDump.h"

namespace zam {
    namespace base {
        namespace log {

            dump_manip_pretty dump_pretty(void* data, size_t data_len) {
                return dump_manip_pretty(data, data_len);
            }

            dump_manip_pretty_bounded dump_pretty(void* data, size_t data_len, size_t max_len) {
                return dump_manip_pretty_bounded(data, data_len, max_len);
            }

            dump_manip_inline dump_inline(void* data, size_t data_len) {
                return boost::log::dump(data, data_len);
            }

            dump_manip_inline_bounded dump_inline(void* data, size_t data_len, size_t max_len) {
                return boost::log::dump(data, data_len, max_len);
            }

        }
    }
}

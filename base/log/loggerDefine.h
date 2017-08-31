//
// Created by SungWoo Yang on 2017. 8. 30..
//

#ifndef ZAM_LOGGERDEFINE_H
#define ZAM_LOGGERDEFINE_H

namespace zam {
    namespace base {
        namespace log {

            enum level {
                trace = 1 << 0,
                debug = 1 << 1,
                info = 1 << 2,
                warning = 1 << 3,
                error = 1 << 4,
                fatal = 1 << 5
            };

        }   // namespace log
    }   // namespace base
}  // namespace zam

#endif //ZAM_LOGGERDEFINE_H

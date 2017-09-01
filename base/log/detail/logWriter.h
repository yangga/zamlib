//
// Created by SungWoo Yang on 2017. 8. 31..
//

#ifndef ZAM_BASE_LOG_DETAIL_LOGWRITER_H
#define ZAM_BASE_LOG_DETAIL_LOGWRITER_H

#include "../loggerDefine.h"

namespace zam {
    namespace base {
        namespace log {

            class logWriter {
            public:
                inline bool checkLevel(level lv) BOOST_NOEXCEPT {
                    return (lv_ & lv);
                }

                virtual void flush(const char* txt);

            private:
                level lv_ = level::all;
            };

        }
    }
}


#endif //ZAM_BASE_LOG_DETAIL_LOGWRITER_H

//
// Created by SungWoo Yang on 2017. 8. 31..
//

#ifndef ZAM_BASE_LOG_DETAIL_LOGGERWRITER_H
#define ZAM_BASE_LOG_DETAIL_LOGGERWRITER_H

#include "../loggerDefine.h"

namespace zam {
    namespace base {
        namespace log {

            class loggerWriter {
            public:
                loggerWriter(std::string name);

                inline bool checkLevel(level lv) BOOST_NOEXCEPT {
                    return (lv_ & lv);
                }

                void flush(const char* txt);

            private:
                std::string name_;
                level lv_ = level::all;
            };

        }
    }
}


#endif //ZAM_BASE_LOG_DETAIL_LOGGERWRITER_H

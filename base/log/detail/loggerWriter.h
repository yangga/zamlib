//
// Created by SungWoo Yang on 2017. 8. 31..
//

#ifndef ZAM_BASE_LOG_DETAIL_LOGGERWRITER_H
#define ZAM_BASE_LOG_DETAIL_LOGGERWRITER_H

#include "base/base.h"

#include "../loggerDefine.h"

#include <boost/log/sinks.hpp>
#include <boost/smart_ptr.hpp>


namespace zam {
    namespace base {
        namespace log {

            class ZAMBASE_API loggerWriter {
            public:
                using sink_t = boost::shared_ptr<boost::log::sinks::sink>;

                explicit loggerWriter(std::string name);

                inline const std::string& getName() const BOOST_NOEXCEPT { return name_; }

                void setLevel(level lv) { lv_ = lv; }

                void addSink(sink_t s);

                inline bool checkLevel(level lv) const BOOST_NOEXCEPT {
                    return (lv_ <= lv);
                }

                void flush(level lvContext, const char* txt);

            private:
                std::string name_;
                level lv_ = level::all;
                std::vector<sink_t> sinks_;
            };

        }
    }
}


#endif //ZAM_BASE_LOG_DETAIL_LOGGERWRITER_H

//
// Created by SungWoo Yang on 2017. 9. 15..
//

#ifndef ZAMLIB_POOL_H
#define ZAMLIB_POOL_H

#include <zam/base/base.h>

#include "../loggerDefine.h"

#include "loggerAppender.h"

#include <boost/serialization/singleton.hpp>

#include <array>

namespace zam {
    namespace base {
        namespace log {

            class appenderPool
                    : public boost::serialization::singleton<appenderPool> {
                friend class boost::serialization::singleton<appenderPool>;

            public:
                inline static appenderPool& instance() { return get_mutable_instance(); }

                loggerAppender* getAppender(streamType type);

            protected:
                appenderPool();

            private:
                std::array<loggerAppender*, streamType::count> appenders_;
            };

        }
    }
}


#endif //ZAMLIB_POOL_H

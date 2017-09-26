//
// Created by SungWoo Yang on 2017. 9. 26..
//

#ifndef ZAMLIB_SCHEDULER_H
#define ZAMLIB_SCHEDULER_H

#include <zam/base/base.h>

#include "../io/ioObject.h"

#include <boost/function.hpp>
#include <boost/timer.hpp>

namespace zam {
    namespace base {
        namespace schedule {

            class scheduler {
            public:
                using delegate_t = boost::function<void()>;

                explicit scheduler(io::ioObject& ioo);

                void once(delegate_t fn, boost::posix_time::time_duration dur);
                void loop(delegate_t fn, boost::posix_time::time_duration dur);

            private:
                io::ioObject& ioo_;
            };

        }
    }
}

#endif //ZAMLIB_SCHEDULER_H

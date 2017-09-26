//
// Created by SungWoo Yang on 2017. 9. 26..
//

#ifndef ZAMLIB_SCHEDULER_H
#define ZAMLIB_SCHEDULER_H

#include <zam/base/base.h>
#include <zam/base/macro.h>

#include "../io/ioObject.h"
#include "../thread/lockObject.h"

#include <boost/enable_shared_from_this.hpp>
#include <boost/timer.hpp>

#include <limits>
#include <map>


namespace zam {
    namespace base {
        namespace schedule {

            class scheduler : public boost::enable_shared_from_this<scheduler>
            {
            public:
                using delegate_t = boost::function<void()>;
                using time_type = typename boost::asio::time_traits<boost::posix_time::ptime>::time_type;
                using duration_type = typename boost::asio::time_traits<boost::posix_time::ptime>::duration_type;

                using timers_t = thread::lockObject< std::map<std::string, boost::shared_ptr<boost::asio::deadline_timer> > >;

                static constexpr auto unlimit_v = (std::numeric_limits<size_t>::max)();

                ZAMBASE_API explicit scheduler(io::ioObject& ioo);

                ZAMBASE_API bool at(std::string name, delegate_t fn, time_type time_at);
                ZAMBASE_API bool once(std::string name, delegate_t fn, duration_type dur);
                ZAMBASE_API bool loop(std::string name, delegate_t fn, duration_type dur, size_t cnt=unlimit_v);
                ZAMBASE_API void stop(std::string name);

                io::ioObject& ioo() { return ioo_; }

            private:
                io::ioObject& ioo_;
                timers_t timers_;
            };

        }
    }
}

#endif //ZAMLIB_SCHEDULER_H

//
// Created by SungWoo Yang on 2017. 9. 16..
//

#ifndef ZAMLIB_IOSYSTEM_H
#define ZAMLIB_IOSYSTEM_H

#include <zam/base/base.h>

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/smart_ptr.hpp>

#include <thread>
#include <vector>

namespace zam {
    namespace base {
        namespace io {

            class ioSystem : boost::noncopyable {
            public:
                ZAMBASE_API
                ioSystem();

                inline boost::asio::io_service &getIos() { return ios_; }

                /// start io service. It gonna be blocked until io_service is stopped.
                ZAMBASE_API
                void start(size_t workerCnt = std::thread::hardware_concurrency());

                ZAMBASE_API
                void stop();

                ZAMBASE_API
                bool stopped() const;

            private:
                boost::asio::io_service ios_;
                boost::asio::io_service::work iosHolder_;

                using thread_ptr = boost::shared_ptr<std::thread>;
                std::vector<thread_ptr> workers_;
            };

        }
    }
}





#endif //ZAMLIB_IOSYSTEM_H

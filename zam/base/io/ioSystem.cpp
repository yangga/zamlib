//
// Created by SungWoo Yang on 2017. 9. 16..
//

#include "ioSystem.h"

#include <boost/bind.hpp>
#include <boost/functional.hpp>

namespace zam {
    namespace base {
        namespace io {

            void ioSystem::start(size_t workerCnt) {
                assert(0 < workerCnt);

                for (size_t i = 0; i < workerCnt; ++i) {
                    workers_.push_back(
                            boost::make_shared<std::thread>([this]() { ios_.run(); })
                    );
                }

                ios_.run();

                for (auto &w : workers_) {
                    w->join();
                }

                workers_.clear();
            }

            void ioSystem::stop() {
                if (!ios_.stopped()) {
                    ios_.stop();
                }
            }

            bool ioSystem::stopped() const {
                return (ios_.stopped() && workers_.empty());
            }

        }
    }
}

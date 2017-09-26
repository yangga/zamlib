//
// Created by SungWoo Yang on 2017. 9. 26..
//

#ifndef ZAMLIB_WAITQ_H
#define ZAMLIB_WAITQ_H

#include <boost/thread.hpp>

#include <queue>
#include <mutex>

namespace zam {
    namespace base {
        namespace container {

            template <typename T>
            class waitq
            {
            public:
                using type = T;
                using queue_type = std::queue<type>;
                using size_type = typename queue_type::size_type;

            public:
                template<class... _Valty>
                bool emplace(_Valty&&... _Val) {
                    if (!isWorking_)
                        return false;

                    std::unique_lock<std::decay_t<decltype(mx_)>> lock(mx_);
                    q_.emplace(std::forward<_Valty>(_Val)...);
                    cond_.notify_one();
                    return true;
                }

                bool push(type const& v) {
                    if (!isWorking_)
                        return false;

                    std::unique_lock<std::decay_t<decltype(mx_)>> lock(mx_);
                    q_.push(v);
                    cond_.notify_one();
                    return true;
                }

                bool pop(type& out) {
                    std::unique_lock<std::decay_t<decltype(mx_)>> lock(mx_);
                    while (q_.empty()) {
                        cond_.wait(lock);

                        if (!isWorking_)
                            break;
                    }

                    if (!isWorking_)
                        return false;

                    std::swap(out, q_.front());
                    q_.pop();

                    return true;
                }

                void clear() {
                    isWorking_ = false;

                    {
                        queue_type tempQ;
                        {
                            std::unique_lock<std::decay_t<decltype(mx_)>> lock(mx_);
                            tempQ.swap(q_);
                        }
                    }

                    cond_.notify_all();
                }

                void reset() {
                    isWorking_ = true;
                }

                inline size_type size() const {
                    return q_.size();
                }

            private:
                bool isWorking_ = true;

                queue_type q_;
                std::mutex mx_;
                std::condition_variable cond_;
            };

        }
    }
}

#endif //ZAMLIB_WAITQ_H

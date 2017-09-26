//
// Created by SungWoo Yang on 2017. 9. 26..
//

#include "scheduler.h"

#include <boost/bind.hpp>

namespace zam {
    namespace base {
        namespace schedule {

            namespace implement {

                void scheduler_remove(scheduler::timers_t& timers, std::string name) {
                    timers.lock([&](scheduler::timers_t::object_t & cont) {
                        auto itr = cont.find(name);
                        if (itr != cont.end()) {
                            cont.erase(itr);
                        }
                    });
                }

                bool scheduler_loop(bool isBegin
                        , boost::shared_ptr<scheduler> s
                        , scheduler::timers_t& timers
                        , std::string name
                        , scheduler::delegate_t fn
                        , scheduler::duration_type dur
                        , size_t cnt) {

                    auto callback = [s, name, fn=std::move(fn), dur, &timers]
                            (const boost::system::error_code& ec, size_t remainCnt) mutable
                    {
                        if (ec) {
                            implement::scheduler_remove(timers, name);
                            return;
                        }

                        if (remainCnt != scheduler::unlimit_v)
                            --remainCnt;

                        if (0 == remainCnt)
                            implement::scheduler_remove(timers, name);

                        fn();

                        if (0 == remainCnt)
                            return;

                        scheduler_loop(false, s, timers, name, fn, dur, remainCnt);
                    };

                    bool isSuccess = false;
                    timers.lock([&](scheduler::timers_t::object_t & cont) {
                        boost::shared_ptr<boost::asio::deadline_timer> timer;
                        if (isBegin) {
                            if (cont.end() == cont.find(name)) {
                                timer = boost::make_shared<boost::asio::deadline_timer>(s->ioo().ios().getIos());
                                cont.insert(std::make_pair(name, timer));
                            }
                        }
                        else {
                            auto itr = cont.find(name);
                            if (itr != cont.end()) {
                                timer = itr->second;
                            }
                        }

                        if (!timer)
                            return;

                        timer->expires_from_now(dur);
                        timer->async_wait(
                                s->ioo().strand().wrap(
                                        boost::bind<void>(
                                                callback, boost::asio::placeholders::error, cnt)));

                        isSuccess = true;
                    });

                    return isSuccess;
                }

            }

            scheduler::scheduler(io::ioObject& ioo)
            : ioo_(ioo)
            {
            }

            bool scheduler::at(std::string name, delegate_t fn, time_type time_at) {
                assert(boost::asio::deadline_timer::traits_type::now() < time_at);
                if (boost::asio::deadline_timer::traits_type::now() >= time_at)
                    return false;

                auto callback = [s=this->shared_from_this(), this, name, fn=std::move(fn)]
                        (const boost::system::error_code& ec)
                {
                    implement::scheduler_remove(timers_, name);

                    if (!ec) {
                        fn();
                    }
                };

                bool isSuccess = false;
                timers_.lock([&](timers_t::object_t & cont) {
                    if (cont.end() != cont.find(name))
                        return;

                    auto timer = boost::make_shared<boost::asio::deadline_timer>(ioo_.ios().getIos());
                    timer->expires_at(time_at);
                    timer->async_wait(
                            ioo_.strand().wrap(
                                    boost::bind<void>(
                                            callback, boost::asio::placeholders::error)));

                    isSuccess = cont.insert(std::make_pair(name, timer)).second;
                });

                return isSuccess;
            }

            bool scheduler::once(std::string name, delegate_t fn, duration_type dur) {
                return loop(std::move(name), std::move(fn), std::move(dur), 1);
            }

            bool scheduler::loop(std::string name, delegate_t fn, duration_type dur, size_t cnt) {
                assert(unlimit_v == cnt || 0 < cnt);
                if (unlimit_v != cnt && 0 == cnt)
                    return false;

                return implement::scheduler_loop(true
                        , this->shared_from_this()
                        , timers_
                        , std::move(name)
                        , std::move(fn)
                        , std::move(dur)
                        , cnt);
            }

            void scheduler::stop(std::string name) {
                timers_.lock([&](timers_t::object_t & cont) {
                    auto itr = cont.find(name);
                    if (itr != cont.end()) {
                        auto& timer = itr->second;
                        boost::system::error_code ec;
                        timer->cancel(ec);
                        cont.erase(itr);
                    }
                });
            }

        }
    }
}

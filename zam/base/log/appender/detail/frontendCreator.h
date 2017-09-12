//
// Created by yangga on 2017. 9. 12..
//

#ifndef ZAMLIB_BASE_LOG_FRONTENDCREATOR_H
#define ZAMLIB_BASE_LOG_FRONTENDCREATOR_H

#include <zam/base/log/loggerDefine.h>

#include <zam/base/log/detail/loggerAttrName.h>

#include <boost/format.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/shared_ptr.hpp>

namespace zam {
    namespace base {
        namespace log {

            namespace detail {

                template<typename SinkBackendT>
                boost::shared_ptr<boost::log::sinks::sink> createGeneralFrontend
                        (std::string channelName
                                , boost::shared_ptr<SinkBackendT> backend
                                , zam::base::log::level thisLevel
                                , bool isUnorder)
                {
                    namespace attrs = boost::log::attributes;
                    namespace sinks = boost::log::sinks;
                    namespace expr = boost::log::expressions;
                    namespace aux = boost::log::sinks::aux;

                    using sink_t = typename aux::make_sink_frontend_base<typename std::decay_t<decltype(backend)>::element_type>::type;
                    boost::shared_ptr<sink_t> sink;

                    if (isUnorder)
                        sink.reset(new sinks::asynchronous_sink<typename std::decay_t<decltype(backend)>::element_type>(backend));
                    else
                        sink.reset(new sinks::synchronous_sink<typename std::decay_t<decltype(backend)>::element_type>(backend));

                    sink->set_formatter(
                            expr::format("%1% (%2%) [%3%] %4%")
                            % expr::format_date_time< boost::posix_time::ptime >(default_attribute_names::timestamp(), "%d %H:%M:%S.%f")
                            % expr::attr<attrs::current_thread_id::value_type>(default_attribute_names::thread_id())
                            % zam_severity
                            % expr::message
                    );

                    sink->set_filter
                            (
                                    expr::attr<level>("Severity") >= thisLevel
                                    && expr::attr< std::string >("Channel") == channelName
                            );

                    return sink;
                }
            }   // namespace detail

        }
    }
}

#endif //ZAMLIB_BASE_LOG_FRONTENDCREATOR_H

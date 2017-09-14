//
// Created by yangga on 2017. 9. 12..
//

#ifndef ZAMLIB_BASE_LOG_FRONTENDCREATOR_H
#define ZAMLIB_BASE_LOG_FRONTENDCREATOR_H

#include "frontendFormatFactory.h"


#include <boost/log/sinks.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/shared_ptr.hpp>

namespace zam {
    namespace base {
        namespace log {
            namespace detail {

                class frontendCreatorFactory;

                /// class frontendCreatorIf
                class frontendCreatorIf
                {
                public:
                    virtual ~frontendCreatorIf() = default;
                    virtual boost::shared_ptr<boost::log::sinks::sink> generate() = 0;

                public:
                    level thisLevel = level::trace;
                    bool isUnorder = false;
                };

                /// class frontendCreator
                template <typename SinkBackendT>
                class frontendCreator : public frontendCreatorIf
                {
                    friend class frontendCreatorFactory;

                public:
                    using char_type = typename SinkBackendT::char_type;
                    using formatter_type = boost::log::basic_formatter< char_type >;

                    void setFormater(formatter_type fmt) { this->fmt = fmt; }

                private:
                    frontendCreator() = default;

                public:
                    boost::shared_ptr<boost::log::sinks::sink> generate() override {
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

                        sink->set_formatter(this->fmt);
                        sink->set_filter(
                                expr::attr<level>("Severity") >= thisLevel
                                && expr::attr< std::string >("Channel") == channelName
                        );

                        return sink;
                    }



                private:
                    std::string channelName;
                    boost::shared_ptr<SinkBackendT> backend;
                    formatter_type fmt;
                };

                /// class frontendCreatorFactory
                class frontendCreatorFactory
                {
                public:
                    template <typename SinkBackendT>
                    static boost::shared_ptr< frontendCreator<SinkBackendT> >
                    get(
                            std::string channelName,
                            boost::shared_ptr<SinkBackendT> backend,
                            formatType fmtType
                    ) {
                        auto c = boost::shared_ptr< frontendCreator<SinkBackendT> >(new frontendCreator<SinkBackendT>());
                        c->channelName = channelName;
                        c->backend = backend;
                        c->setFormater(frontendFormatFactory<typename SinkBackendT::char_type>::get(fmtType));
                        return c;
                    }
                };







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

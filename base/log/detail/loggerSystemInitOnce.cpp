//
// Created by SungWoo Yang on 2017. 9. 3..
//

#include "loggerSystemInitOnce.h"

#include <boost/core/null_deleter.hpp>
#include <boost/log/common.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/exception_handler.hpp>
#include <boost/log/utility/record_ordering.hpp>
#include <boost/log/support/date_time.hpp>


namespace zam {
    namespace base {
        namespace log {

            namespace logging = boost::log;
            namespace attrs = boost::log::attributes;



            struct my_log_exception_handler
            {
                void operator()(const logging::runtime_error &ex) const
                {
                    std::cerr << "boost::log::runtime_error: " << ex.what() << '\n';
                }

                void operator()(const std::exception &ex) const
                {
                    std::cerr << "std::exception: " << ex.what() << '\n';
                }
            };

            loggerSystemInitOnce::loggerSystemInitOnce() {
                boost::log::core::get()->set_exception_handler(logging::make_exception_handler<logging::runtime_error, std::exception>(my_log_exception_handler()));

                // global attributes
                logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
                logging::core::get()->add_global_attribute(boost::log::aux::default_attribute_names::process_id(), attrs::current_process_id());
                logging::core::get()->add_global_attribute(boost::log::aux::default_attribute_names::thread_id(), attrs::current_thread_id());
            }

        }
    }
}

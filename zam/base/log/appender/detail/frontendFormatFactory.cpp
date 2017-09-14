//
// Created by SungWoo Yang on 2017. 9. 14..
//

#include "frontendFormatFactory.h"

#include <boost/log/support/date_time.hpp>


namespace zam {
    namespace base {
        namespace log {
            namespace detail {

                boost::log::basic_formatter<char>
                frontendFormatFactory<char>::get(formatType fmt) {

                    namespace expr = boost::log::expressions;
                    namespace attrs = boost::log::attributes;

                    switch (fmt) {
                        case formatType::normal:
                            return expr::format("%1% (%2%) [%3%] %4%")
                                   % expr::format_date_time<boost::posix_time::ptime>(
                                    default_attribute_names::timestamp(), "%d %H:%M:%S.%f")
                                   % expr::attr<attrs::current_thread_id::value_type>(
                                    default_attribute_names::thread_id())
                                   % zam_severity
                                   % expr::message;
                        case formatType::xml:
                            return expr::format("<record time=\"%1%\" tid=\"%2%\" level=\"%3%\">%4%</record>")
                                   % expr::format_date_time<boost::posix_time::ptime>(
                                    default_attribute_names::timestamp(), "%d %H:%M:%S.%f")
                                   % expr::attr<attrs::current_thread_id::value_type>(
                                    default_attribute_names::thread_id())
                                   % zam_severity
                                   % expr::message;
                        case formatType::json:
                            return expr::format("{time:\"%1%\", tid:\"%2%\", level:\"%3%\", content=\"%4%\"},")
                                   % expr::format_date_time<boost::posix_time::ptime>(
                                    default_attribute_names::timestamp(), "%d %H:%M:%S.%f")
                                   % expr::attr<attrs::current_thread_id::value_type>(
                                    default_attribute_names::thread_id())
                                   % zam_severity
                                   % expr::message;
                        default:
                            break;
                    }

                    throw std::invalid_argument("invalid log format type");
                    return expr::format("");
                }
            }
        }
    }
}
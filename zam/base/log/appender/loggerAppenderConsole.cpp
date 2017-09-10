//
// Created by SungWoo Yang on 2017. 9. 1..
//

#include "loggerAppenderConsole.h"

#include "zam/base/log/detail/loggerAttrName.h"
#include "zam/base/log/detail/loggerWriter.h"

#include <boost/core/null_deleter.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/record_ordering.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

#include "external/JsonValueCaster/JsonValueCaster.h"


namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

namespace zam {
    namespace base {
        namespace log {

#ifdef _WINDOWS
            // color print console backend
            class clr_text_ostream_backend : public boost::log::sinks::text_ostream_backend
            {
                static uint16_t get_color(level level) {
                    switch (level)
                    {
                        case level::trace: return 0x08;
                        case level::debug: return 0x07;
                        case level::info: return 0x0F;
                        case level::warn: return 0x0D;
                        case level::error: return 0x0E;
                        case level::fatal: return 0x0C;
                        default: break;
                    }

                    return 0x0F;
                }

            public:
                void consume(boost::log::record_view const& rec, string_type const& formatted_string) {
                    auto lv = rec.attribute_values()["Severity"].extract<level>();
                    
                    auto hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

                    CONSOLE_SCREEN_BUFFER_INFO csbi;
                    GetConsoleScreenBufferInfo(hstdout, &csbi);
                    SetConsoleTextAttribute(hstdout, get_color(lv.get()));

                    boost::log::sinks::text_ostream_backend::consume(rec, formatted_string);

                    SetConsoleTextAttribute(hstdout, csbi.wAttributes);
                }
            };
#else
            // color print console backend
            class clr_text_ostream_backend : public boost::log::sinks::text_ostream_backend
            {
                static const char* get_color(level level) {
                    switch (level)
                    {
                        /// reference : https://misc.flogisoft.com/bash/tip_colors_and_formatting
                        case level::trace: return "\033[90m";
                        case level::debug: return "\033[37m";
                        case level::info: return "\033[33m";
                        case level::warn: return "\033[32m";
                        case level::error: return "\033[31m";
                        case level::fatal: return "\033[36m";
                        default: break;
                    }

                    return "";
                }

            public:
                void consume(boost::log::record_view const& rec, string_type const& formatted_string) {
                    auto lv = rec.attribute_values()["Severity"].extract<level>();

                    auto clr = get_color(lv.get());
                    boost::log::sinks::text_ostream_backend::consume(rec, clr + formatted_string + "\033[0m");
                }
            };
#endif

            void loggerAppenderConsole::load(loggerWriter &writer, Json::Value const & vAppender) {
                Json::CasterCoverDef const c(vAppender);
                auto const thisLevel = toLevel(c.get<std::string>("level", "all").c_str());

                auto consoleSinkCreator = [thisLevel=thisLevel, &writer](auto backend) mutable {
                    backend->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));
                    backend->auto_flush(true);

                    using sink_t = sinks::synchronous_sink<typename std::decay_t<decltype(backend)>::element_type>;
                    auto sink = boost::make_shared<sink_t>(backend);

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
                                    && expr::attr< std::string >("Channel") == writer.getName()
                            );

                    logging::core::get()->add_sink(sink);
                    writer.addSink(sink);
                };

                consoleSinkCreator(boost::make_shared<clr_text_ostream_backend>());
                //consoleSinkCreator(boost::make_shared<sinks::text_ostream_backend>());
            }

        }
    }
}

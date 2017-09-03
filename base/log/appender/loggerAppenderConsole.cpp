//
// Created by SungWoo Yang on 2017. 9. 1..
//

#include "base.h"
#include "loggerAppenderConsole.h"

#include "../detail/loggerWriter.h"


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


namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

namespace zam {
    namespace base {
        namespace log {

            /*
            // color print console backend
            class clr_text_ostream_backend : public boost::log::sinks::text_ostream_backend
            {
            public:
                static WORD get_colour(CFCBase::CLog::severity_level level)
                {
                    switch (level)
                    {
                        case CFCBase::CLog::severity_level::trace: return 0x08;
                        case CFCBase::CLog::severity_level::debug: return 0x07;
                        case CFCBase::CLog::severity_level::info: return 0x0F;
                        case CFCBase::CLog::severity_level::warning: return 0x0D;
                        case CFCBase::CLog::severity_level::error: return 0x0E;
                        case CFCBase::CLog::severity_level::fatal: return 0x0C;
                        default: return 0x0F;
                    }
                }

                void consume(boost::log::record_view const& rec, string_type const& formatted_string) {
                    auto level = rec.attribute_values()["Severity"].extract<CFCBase::CLog::severity_level>();
                    auto hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

                    CONSOLE_SCREEN_BUFFER_INFO csbi;
                    GetConsoleScreenBufferInfo(hstdout, &csbi);
                    SetConsoleTextAttribute(hstdout, get_colour(level.get()));

                    boost::log::sinks::text_ostream_backend::consume(rec, formatted_string);

                    SetConsoleTextAttribute(hstdout, csbi.wAttributes);
                }
            };
             */

            void loggerAppenderConsole::load(loggerWriter &writer, Json::Value const & vAppender) {
                const level thisLevel = toLevel(vAppender["level"].asCString());

                auto consoleSinkCreator = [thisLevel=thisLevel, &writer](auto backend) mutable {
                    backend->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));
                    backend->auto_flush(true);

                    using sink_t = sinks::synchronous_sink<typename std::decay_t<decltype(backend)>::element_type>;
                    auto sink = boost::make_shared<sink_t>(backend);

                    sink->set_formatter(
                            expr::format("%1% (%2%) [%3%] %4%")
                            % expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%d %H:%M:%S.%f")
                            % expr::attr<attrs::current_thread_id::value_type>("ThreadID")
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

                /*
                bool isColorPrint = true;

                if (isColorPrint) {
                    consoleSinkCreator(boost::make_shared<clr_text_ostream_backend>());
                }
                else {
                    consoleSinkCreator(boost::make_shared<sinks::text_ostream_backend>());
                }
                 */

                consoleSinkCreator(boost::make_shared<sinks::text_ostream_backend>());
            }

        }
    }
}

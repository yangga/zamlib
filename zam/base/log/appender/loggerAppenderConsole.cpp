//
// Created by SungWoo Yang on 2017. 9. 1..
//

#include "loggerAppenderConsole.h"

#include "detail/frontendCreator.h"

#include "zam/base/log/detail/loggerWriter.h"

#include <boost/core/null_deleter.hpp>

#include "external/JsonValueCaster/JsonValueCaster.h"


namespace logging = boost::log;
namespace sinks = boost::log::sinks;

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

            template <typename Backend_t>
            boost::shared_ptr<Backend_t> createTextOStreamBackend() {
                auto backend = boost::make_shared<Backend_t>();
                backend->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));
                backend->auto_flush(true);
                return backend;
            }

            void loggerAppenderConsole::load(loggerWriter &writer, Json::Value const & vAppender) {
                Json::CasterCoverDef const c(vAppender);
                auto const thisLevel = toLevel(c.get<std::string>("all", "level").c_str());
                auto const fmtType = toFormatType(c.get<std::string>("plain", "format").c_str());

                Json::CasterBoolean jcb(vAppender);
                auto const isColor = jcb.get("color", false);
                auto const isUnorder = jcb.get("unorder", false);

                boost::shared_ptr<detail::frontendCreatorIf> creator;
                if (isColor)
                    creator = detail::frontendCreatorFactory::get(writer.getName(), createTextOStreamBackend<clr_text_ostream_backend>(), fmtType);
                else
                    creator = detail::frontendCreatorFactory::get(writer.getName(), createTextOStreamBackend<sinks::text_ostream_backend>(), fmtType);

                creator->thisLevel = thisLevel;
                creator->isUnorder = isUnorder;
                auto sink = creator->generate();

                logging::core::get()->add_sink(sink);
                writer.addSink(sink);
            }

        }
    }
}

//
// Created by yangga on 2017. 9. 14..
//

#include "loggerAppenderSyslog.h"

#include "detail/frontendCreator.h"

#include "zam/base/log/detail/loggerWriter.h"

#include "external/JsonValueCaster/JsonValueCaster.h"

#include <boost/log/sinks/syslog_backend.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace zam {
    namespace base {
        namespace log {

            void loggerAppenderSyslog::load(loggerWriter &writer, Json::Value const& vAppender) {

#ifdef BOOST_LOG_USE_NATIVE_SYSLOG

                Json::CasterCoverDef const c(vAppender);

                auto const url(c.get<std::string>("localhost", "url"));
                auto const port(c.get<unsigned short>(514, "port"));
                auto const thisLevel = toLevel(c.get<std::string>("all", "level").c_str());
                auto const fmtType = toFormatType(c.get<std::string>("normal", "format").c_str());

                auto backend = boost::make_shared<sinks::syslog_backend>();

                sinks::syslog::custom_severity_mapping<level> mapping("Severity");
                mapping[trace] = sinks::syslog::debug;
                mapping[debug] = sinks::syslog::debug;
                mapping[info] = sinks::syslog::info;
                mapping[warn] = sinks::syslog::warning;
                mapping[error] = sinks::syslog::error;
                mapping[fatal] = sinks::syslog::critical;
                backend->set_severity_mapper(mapping);

                backend->set_target_address(url, port);

                Json::CasterBoolean jcb(vAppender);
                auto const isUnorder = jcb.get("unorder", false);

                auto creator = detail::frontendCreatorFactory::get(writer.getName(), backend, fmtType);
                creator->thisLevel = thisLevel;
                creator->isUnorder = isUnorder;
                auto sink = creator->generate();

                logging::core::get()->add_sink(sink);
                writer.addSink(sink);

#else

                std::cout << "Native syslog API is not supported on this platform" << std::endl;

#endif

            }

        }
    }
}

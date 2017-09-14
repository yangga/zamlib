//
// Created by SungWoo Yang on 2017. 9. 2..
//

#include "loggerAppenderTracer.h"

#include "detail/frontendCreator.h"

#include "zam/base/log/detail/loggerWriter.h"

#include "external/JsonValueCaster/JsonValueCaster.h"

#include <boost/log/sinks/debug_output_backend.hpp>


namespace logging = boost::log;
namespace sinks = boost::log::sinks;

namespace zam {
    namespace base {
        namespace log {

            void loggerAppenderTracer::load(loggerWriter &writer, Json::Value const &vAppender) {
#ifdef BOOST_WINDOWS
                Json::CasterCoverDef const c(vAppender);
                auto const thisLevel = toLevel(c.get<std::string>("all", "level").c_str());
                auto const fmtType = toFormatType(c.get<std::string>("normal", "format").c_str());

                Json::CasterBoolean jcb(vAppender);
                auto const isUnorder = jcb.get("unorder", false);

                auto creator = detail::frontendCreatorFactory::get(writer.getName(), boost::make_shared<sinks::debug_output_backend>(), fmtType);
                creator->thisLevel = thisLevel;
                creator->isUnorder = isUnorder;
                auto sink = creator->generate();

                logging::core::get()->add_sink(sink);
                writer.addSink(sink);
#endif
            }

        }
    }
}

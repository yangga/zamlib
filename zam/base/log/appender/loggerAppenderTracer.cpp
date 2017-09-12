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
                auto const thisLevel = toLevel(c.get<std::string>("level", "all").c_str());

                Json::CasterBoolean jcb(vAppender);
                auto const isUnorder = jcb.get("unorder", false);

                auto sink = detail::createGeneralFrontend(writer.getName(), boost::make_shared<sinks::debug_output_backend>(), thisLevel, isUnorder);

                logging::core::get()->add_sink(sink);
                writer.addSink(sink);
#endif
            }

        }
    }
}

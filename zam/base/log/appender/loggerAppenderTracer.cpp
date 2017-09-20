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

			class debug_output_backend_newline : public sinks::debug_output_backend
			{
			public:
				void consume(boost::log::record_view const& rec, string_type const& formatted_message) {
					sinks::debug_output_backend::consume(rec, formatted_message + "\n");
				}
			};

            void loggerAppenderTracer::load(loggerWriter &writer, Json::Value const &vAppender) {
#ifdef BOOST_WINDOWS
                Json::CasterCoverDef const c(vAppender);
                auto const thisLevel = toLevel(c.get<std::string>("all", "level").c_str());
                auto const fmtType = toFormatType(c.get<std::string>("plain", "format").c_str());

                Json::CasterBoolean jcb(vAppender);
                auto const isUnorder = jcb.get("unorder", false);
				
                auto creator = detail::frontendCreatorFactory::get(writer.getName(), boost::make_shared<debug_output_backend_newline>(), fmtType);
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

//
// Created by SungWoo Yang on 2017. 9. 1..
//

#include "loggerAppenderFile.h"

#include "detail/frontendCreator.h"

#include "zam/base/log/detail/loggerWriter.h"

#include "zam/base/log/appender/collector/collectorDefault.h"

#include "external/JsonValueCaster/JsonValueCaster.h"

#include <boost/lambda/lambda.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace zam {
    namespace base {
        namespace log {

            void loggerAppenderFile::load(loggerWriter &writer, Json::Value const& vAppender) {
                Json::CasterCoverDef const c(vAppender);

                auto const filename(c.get<std::string>("log.log", "fileName"));
                auto const dirPath(c.get<std::string>("./logs", "path"));
                auto const thisLevel = toLevel(c.get<std::string>("all", "level").c_str());
                auto const fmtType = toFormatType(c.get<std::string>("normal", "format").c_str());

                auto file_backend = boost::make_shared<sinks::text_file_backend>(
                        keywords::file_name = boost::filesystem::path(dirPath) / boost::filesystem::path(filename)
                );

                auto rollSize = c.get<uint64_t>(0, "maxFileByte");
                if (0 < rollSize)
                    file_backend->set_rotation_size(rollSize);

                auto rollSecond = c.get<long>(0, "rollSecond");
                if (0 < rollSecond)
                    file_backend->set_time_based_rotation(sinks::file::rotation_at_time_interval(boost::posix_time::minutes(rollSecond)));

                file_backend->auto_flush(true);

                file_backend->set_file_collector(boost::make_shared <collector::collectorDefault>(filename, dirPath));

                Json::CasterBoolean jcb(vAppender);
                auto const isUnorder = jcb.get("unorder", false);

                auto creator = detail::frontendCreatorFactory::get(writer.getName(), file_backend, fmtType);
                creator->thisLevel = thisLevel;
                creator->isUnorder = isUnorder;
                auto sink = creator->generate();

#ifdef BOOST_WINDOWS
                const char* newline = "\n\r";
#else
                const char* newline = "\n";
#endif

                switch (fmtType) {
                    case formatType::xml:
                    {
                        namespace bll = boost::lambda;
                        file_backend->set_open_handler
                                (
                                        bll::_1 << "<?xml version=\"1.0\"?>" << newline << "<log>" << newline
                                );
                        file_backend->set_close_handler
                                (
                                        bll::_1 << "</log>" << newline
                                );
                    }
                        break;
                    case formatType::json:
                    {
                        namespace bll = boost::lambda;
                        file_backend->set_open_handler
                                (
                                        bll::_1 << "{" << newline
                                );
                        file_backend->set_close_handler
                                (
                                        bll::_1 << "{}}" << newline
                                );
                    }
                        break;
                    default:
                        break;
                }

                logging::core::get()->add_sink(sink);
                writer.addSink(sink);

                try {
                    file_backend->scan_for_files();
                }
                catch(...){}
            }

        }
    }
}


//
// Created by SungWoo Yang on 2017. 9. 1..
//

#include "loggerAppenderFile.h"

#include "zam/base/log/detail/loggerAttrName.h"
#include "zam/base/log/detail/loggerWriter.h"

#include "zam/base/log/appender/collector/collectorDefault.h"

#include <boost/core/null_deleter.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/log/common.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/record_ordering.hpp>
#include <boost/log/support/date_time.hpp>

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

            void loggerAppenderFile::load(loggerWriter &writer, Json::Value const& vAppender) {
                Json::CasterCoverDef const c(vAppender);

                auto const filename(c.get<std::string>("fileName", "log.log"));
                auto const dirPath(c.get<std::string>("path", "./logs"));
                auto const thisLevel = toLevel(c.get<std::string>("level", "all").c_str());

                boost::shared_ptr< sinks::text_file_backend > file_backend = boost::make_shared< sinks::text_file_backend >(
                        keywords::file_name = boost::filesystem::path(dirPath) / boost::filesystem::path(filename)
                );

                auto rollSize = c.get<uint64_t>("maxFileByte", 0);
                if (0 < rollSize)
                    file_backend->set_rotation_size(rollSize);

                auto rollSecond = c.get<long>("rollSecond", 0);
                if (0 < rollSecond)
                    file_backend->set_time_based_rotation(sinks::file::rotation_at_time_interval(boost::posix_time::minutes(rollSecond)));

                file_backend->auto_flush(true);

                using sink_t = sinks::synchronous_sink<sinks::text_file_backend>;
                boost::shared_ptr< sink_t > sink(new sink_t(file_backend));

                auto my_col = boost::make_shared <collector::collectorDefault>(filename, dirPath);
                sink->locked_backend()->set_file_collector(my_col);

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

                try
                {
                    sink->locked_backend()->scan_for_files();
                }
                catch (...)
                {
                }
            }

        }
    }
}


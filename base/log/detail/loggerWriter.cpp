//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include "loggerWriter.h"

#include <boost/log/common.hpp>

namespace zam {
    namespace base {
        namespace log {

            loggerWriter::loggerWriter(std::string name)
                : name_(std::move(name))
            {
            }

            void loggerWriter::addSink(sink_t s) {
                sinks_.push_back(s);
            }

            void loggerWriter::flush(level lvContext, const char* txt) {
                namespace src = boost::log::sources;
                namespace keywords = boost::log::keywords;

                src::severity_channel_logger_mt<level> logger(keywords::channel = name_);
	            BOOST_LOG_SEV(logger, lvContext) << txt;
            }

        }
    }
}

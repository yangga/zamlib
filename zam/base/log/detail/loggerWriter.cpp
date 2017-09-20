//
// Created by SungWoo Yang on 2017. 9. 20..
//

#include "loggerWriter.h"

namespace zam {
    namespace base {
        namespace log {

            void loggerWriter::addSink(sink_t s) {
                sinks_.push_back(s);
            }

            void loggerWriter::flush(level lvContext, const char* txt) {
                if (lvContext < lv_)
                    return;

                namespace src = boost::log::sources;
                namespace keywords = boost::log::keywords;

                src::severity_channel_logger_mt<level> logger(keywords::channel = name_);
                BOOST_LOG_SEV(logger, lvContext) << txt;
            }

        }
    }
}

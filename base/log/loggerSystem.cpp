//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include "base.h"
#include "loggerSystem.h"

#include "loggerDefine.h"

#include "base/log/detail/loggerWriter.h"
#include "detail/loggerPool.h"

#include "base/log/appender/loggerAppenderConsole.h"
#include "base/log/appender/loggerAppenderFile.h"
#include "base/log/appender/loggerAppenderTracer.h"
#include "base/log/appender/loggerAppenderUdp.h"

#include <json/json.h>

#include <fstream>

namespace zam {
    namespace base {
        namespace log {

            struct {
                streamType type;
                loggerAppender* allocator;
            } __log_appenders__[] = {
                    { streamType::console, new loggerAppenderConsole },
                    { streamType::file, new loggerAppenderFile },
                    { streamType::tracer, new loggerAppenderTracer },
                    { streamType::udp, new loggerAppenderUdp }
            };


            void loggerSystem::allocate(const char* tag, Json::Value const& vAppenderList) {
                static auto findAppender = [&](Json::Value const& vAppender) -> loggerAppender* {
                    auto type = toStreamType(vAppender["stream"].asString().c_str());
                    for (auto const& ele : __log_appenders__) {
                        if (ele.type == type)
                            return ele.allocator;
                    }
                    return nullptr;
                };

                try {

                    for (auto const& vAppender : vAppenderList) {
                        auto appender = findAppender(vAppender);
                        if (nullptr == appender)
                            throw std::invalid_argument("no stream");

                        appender->load(*loggerPool::instance().get(tag), vAppender);
                    }
                } catch(std::exception& e) {
                    throw std::logic_error(std::string(e.what()) + " - tag:" + tag);
                }
            }

            void loggerSystem::load(Json::Value const& vCfg) {
                if (!vCfg.isObject())
                    throw std::invalid_argument("logger config json-value is must be object type");

                for (auto const& tag : vCfg.getMemberNames()) {
                    allocate(tag.c_str(), vCfg[tag]["appender"]);
                }
            }

            void loggerSystem::load(const char* filename) {
                std::ifstream file(filename);

                Json::Value root;
                file >> root;
                load(root);
            }

        }
    }
}

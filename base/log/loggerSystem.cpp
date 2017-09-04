//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include "base.h"
#include "loggerSystem.h"

#include "loggerDefine.h"

#include "detail/loggerWriter.h"
#include "detail/loggerPool.h"
#include "detail/loggerSystemInitOnce.h"

#include "appender/loggerAppenderConsole.h"
#include "appender/loggerAppenderFile.h"
#include "appender/loggerAppenderTracer.h"
#include "appender/loggerAppenderUdp.h"

#include <json/json.h>

#include <external/JsonValueCaster/JsonValueCaster.h>

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
                static loggerSystemInitOnce __loggerSystemInitOnce__;

                static auto getAppender = [&](Json::Value const& vAppender) -> loggerAppender* {
                    auto type = toStreamType(vAppender["stream"].asString().c_str());
                    for (auto const& ele : __log_appenders__) {
                        if (ele.type == type)
                            return ele.allocator;
                    }
                    return nullptr;
                };

                static auto getLevel = [&](Json::Value const& vAppender) -> level {
                    return toLevel(vAppender["level"].asCString());
                };

                try {
                    loggerWriter* writer = loggerPool::instance().alloc(tag);

                    for (auto const& vAppender : vAppenderList) {
                        auto appender = getAppender(vAppender);
                        if (nullptr == appender)
                            throw std::invalid_argument("invalid stream");

                        appender->load(*writer, vAppender);
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

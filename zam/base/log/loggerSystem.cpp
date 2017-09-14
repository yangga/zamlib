//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include "loggerSystem.h"

#include "loggerDefine.h"

#include "zam/base/log/detail/loggerWriter.h"
#include "zam/base/log/detail/loggerPool.h"
#include "zam/base/log/detail/loggerSystemInitOnce.h"

#include "zam/base/log/appender/loggerAppenderConsole.h"
#include "zam/base/log/appender/loggerAppenderFile.h"
#include "zam/base/log/appender/loggerAppenderTracer.h"
#include "zam/base/log/appender/loggerAppenderSyslog.h"
#include "zam/base/log/appender/loggerAppenderUdp.h"

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
                    { streamType::syslog, new loggerAppenderSyslog },
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
                static auto getLevel = [&](Json::Value const& vAppender) -> level {
                    try {
                        return toLevel(Json::CasterStatic::Get<const char*>(vAppender, "level"));
                    } catch(...) {
                    }
                    return level::all;
                };

                if (!vCfg.isObject())
                    throw std::invalid_argument("logger config json-value is must be object type");

                for (auto const& tag : vCfg.getMemberNames()) {
                    loggerWriter* writer = loggerPool::instance().alloc(tag);
                    writer->setLevel(getLevel(vCfg[tag]));

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

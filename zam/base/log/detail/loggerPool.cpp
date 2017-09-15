//
// Created by SungWoo Yang on 2017. 9. 2..
//

#include "loggerPool.h"

#include "loggerWriter.h"

#include "../appender/appenderPool.h"

#include <json/value.h>

namespace zam {
    namespace base {
        namespace log {

            loggerPool::loggerPool()
            : defaultWriter_(boost::make_shared<loggerWriter>("$$__default__$$")){
                /// allocated default logger for unexpected situation. (ex. no logger is configured)
                Json::Value vCfg;
                vCfg["level"] = "trace";
                vCfg["format"] = "plain";

                appenderPool::instance().getAppender(streamType::console)->load(*defaultWriter_.get(), vCfg);
            }

            loggerPool::~loggerPool() {
                for (auto itr : writers_) {
                    delete itr.second;
                }
                writers_.clear();
            }

            loggerWriter* loggerPool::alloc(std::string const& name) {
                auto itr = writers_.find(name);
                if (itr != writers_.end())
                    return itr->second;

                return writers_.insert(std::make_pair(name, new loggerWriter(name))).first->second;
            }

            loggerWriter* loggerPool::get(std::string const& name) const BOOST_NOEXCEPT {
                auto itr = writers_.find(name);
                if (itr != writers_.end())
                    return itr->second;

                return defaultWriter_.get();
            }

        }
    }
}

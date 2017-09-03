//
// Created by SungWoo Yang on 2017. 9. 2..
//

#include "loggerPool.h"

#include "loggerWriter.h"

namespace zam {
    namespace base {
        namespace log {

            loggerPool& loggerPool::instance() {
                return boost::serialization::singleton<loggerPool>::get_mutable_instance();
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

                return nullptr;
            }

        }
    }
}

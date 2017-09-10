//
// Created by SungWoo Yang on 2017. 9. 2..
//

#ifndef ZAM_LOGGERPOOL_H
#define ZAM_LOGGERPOOL_H

#include "base/base.h"

#include <boost/serialization/singleton.hpp>

#include <map>

namespace zam {
    namespace base {
        namespace log {

            class loggerWriter;

            class loggerPool
                    : public boost::serialization::singleton<loggerPool> {
                friend class boost::serialization::singleton<loggerPool>;

            public:
				inline static loggerPool& instance() { return get_mutable_instance(); }

                loggerWriter* alloc(std::string const& name);
				loggerWriter* get(std::string const& name) const BOOST_NOEXCEPT;

            private:
                std::map<std::string, loggerWriter*> writers_;
            };

        }
    }
}


#endif //ZAM_LOGGERPOOL_H

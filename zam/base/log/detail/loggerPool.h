//
// Created by SungWoo Yang on 2017. 9. 2..
//

#ifndef ZAM_LOGGERPOOL_H
#define ZAM_LOGGERPOOL_H

#include <zam/base/base.h>

#include <boost/serialization/singleton.hpp>
#include <boost/smart_ptr.hpp>

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

                ~loggerPool();

            protected:
                loggerPool();

            private:
                std::map<std::string, loggerWriter*> writers_;

                boost::shared_ptr<loggerWriter> defaultWriter_;
            };

        }
    }
}


#endif //ZAM_LOGGERPOOL_H

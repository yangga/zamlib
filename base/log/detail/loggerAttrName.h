//
// Created by SungWoo Yang on 2017. 9. 5..
//

#ifndef ZAMLIB_BASE_LOG_LOGGERATTRNAME_H
#define ZAMLIB_BASE_LOG_LOGGERATTRNAME_H

#include <boost/log/attributes.hpp>
#include <boost/log/detail/default_attribute_names.hpp>

namespace zam {
    namespace base {
        namespace log {
            namespace default_attribute_names  = boost::log::aux::default_attribute_names;




        }
    }
}

namespace boost{ namespace log{ namespace aux{ namespace default_attribute_names{
                boost::log::attribute_name hostname();
}}}}

#endif //ZAMLIB_BASE_LOG_LOGGERATTRNAME_H

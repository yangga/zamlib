//
// Created by SungWoo Yang on 2017. 9. 5..
//

#ifndef ZAMLIB_BASE_LOG_LOGGERATTRNAME_H
#define ZAMLIB_BASE_LOG_LOGGERATTRNAME_H

#include <zam/base/base.h>

#include <boost/log/attributes.hpp>
#include <boost/log/detail/default_attribute_names.hpp>

namespace zam {
    namespace base {
        namespace log {
            namespace default_attribute_names {

                ZAMBASE_API boost::log::attribute_name severity();
                ZAMBASE_API boost::log::attribute_name channel();
                ZAMBASE_API boost::log::attribute_name message();
                ZAMBASE_API boost::log::attribute_name line_id();
                ZAMBASE_API boost::log::attribute_name timestamp();
                ZAMBASE_API boost::log::attribute_name process_id();
                ZAMBASE_API boost::log::attribute_name thread_id();

                ZAMBASE_API boost::log::attribute_name hostname();
            }

        }
    }
}


#endif //ZAMLIB_BASE_LOG_LOGGERATTRNAME_H

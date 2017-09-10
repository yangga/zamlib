//
// Created by SungWoo Yang on 2017. 9. 5..
//

#include "loggerAttrName.h"

#define RETURN_BOOST_DEF_ATTR(_TAG_)    return boost::log::aux::default_attribute_names::_TAG_()

namespace zam {
    namespace base {
        namespace log {
            namespace default_attribute_names {

                boost::log::attribute_name severity() { RETURN_BOOST_DEF_ATTR(severity); }
                boost::log::attribute_name channel() { RETURN_BOOST_DEF_ATTR(channel); }
                boost::log::attribute_name message() { RETURN_BOOST_DEF_ATTR(message); }
                boost::log::attribute_name line_id() { RETURN_BOOST_DEF_ATTR(line_id); }
                boost::log::attribute_name timestamp() { RETURN_BOOST_DEF_ATTR(timestamp); }
                boost::log::attribute_name process_id() { RETURN_BOOST_DEF_ATTR(process_id); }
                boost::log::attribute_name thread_id() { RETURN_BOOST_DEF_ATTR(thread_id); }

                boost::log::attribute_name hostname() { return "HostName"; }

            }
        }
    }
}





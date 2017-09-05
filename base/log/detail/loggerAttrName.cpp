//
// Created by SungWoo Yang on 2017. 9. 5..
//

#include "base.h"
#include "loggerAttrName.h"

namespace boost{ namespace log{ namespace aux{ namespace default_attribute_names{

boost::log::attribute_name hostname() {
    return boost::log::attribute_name("HostName");
}

}}}}
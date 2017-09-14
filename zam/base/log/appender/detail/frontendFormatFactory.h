//
// Created by SungWoo Yang on 2017. 9. 14..
//

#ifndef ZAMLIB_FRONTENDFORMATFACTORY_H
#define ZAMLIB_FRONTENDFORMATFACTORY_H

#include <zam/base/log/loggerDefine.h>

#include <zam/base/log/detail/loggerAttrName.h>

#include <boost/format.hpp>
#include <boost/log/expressions.hpp>

namespace zam {
    namespace base {
        namespace log {
            namespace detail {


                template <typename CharT>
                class frontendFormatFactory {
                public:
                    static boost::log::basic_formatter<CharT> get(formatType fmt) {
                        return boost::log::basic_formatter<CharT>();
                    }
                };

                /// only 'char' type is supported now
                template <>
                class frontendFormatFactory<char> {
                public:
                    static boost::log::basic_formatter<char> get(formatType fmt);
                };

            }
        }
    }
}


#endif //ZAMLIB_FRONTENDFORMATFACTORY_H

//
// Created by SungWoo Yang on 2017. 9. 24..
//

#ifndef ZAMLIB_FORMS_H
#define ZAMLIB_FORMS_H

#include "formBinary.h"
#include "formJson.h"
#include "formProtobuf.h"

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/vector.hpp>

#include <type_traits>

namespace zam {
    namespace net {
        namespace proto {

            using proto_form_sequence = boost::mpl::vector
                    <
                            formJson,

                            formBinary	// this form must be placed at the end
                    >;

            struct proto_form_predicate {
                template<typename SEQUENCE, typename PROTO_DATA_T>
                struct apply {
                    static constexpr bool value = SEQUENCE::template check_value<PROTO_DATA_T>();
                };
            };

            template <typename PROTO_DATA_T>
            struct proto_form_factory_impl {
                using iterator_type = typename boost::mpl::find_if
                        <
                                proto_form_sequence,
                                proto_form_predicate::apply<boost::mpl::_1, PROTO_DATA_T>
                        >::type;

                using type = typename boost::mpl::deref<iterator_type>::type;
            };

        }
    }
}

#endif //ZAMLIB_FORMS_H

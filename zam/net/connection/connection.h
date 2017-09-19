//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_CONNECTION_H
#define ZAMLIB_CONNECTION_H

#include <boost/enable_shared_from_this.hpp>

namespace zam {
    namespace net {

        struct connection : public boost::enable_shared_from_this<connection>
        {

        };

    }
}

#endif //ZAMLIB_CONNECTION_H

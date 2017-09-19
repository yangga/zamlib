//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_CONNECTIONIO_H
#define ZAMLIB_CONNECTIONIO_H

#include "connection.h"

#include <zam/base/io/ioObject.h>

namespace zam {
    namespace net {

        class connectionIO
                : public base::io::ioObject
                , public connection
        {
        protected:
            connectionIO(base::io::ioSystem& ios) : base::io::ioObject(ios) {}
        };

    }
}

#endif //ZAMLIB_CONNECTIONIO_H

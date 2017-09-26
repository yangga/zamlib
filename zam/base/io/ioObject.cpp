//
// Created by SungWoo Yang on 2017. 9. 26..
//

#include "ioObject.h"

namespace zam {
    namespace base {
        namespace io {

            ioObject::ioObject(ioObject& ioo)
            : ioObject(ioo.ios())
            {
            }

            ioObject::ioObject(ioSystem& ios)
                    : ios_(ios)
                    , strand_(ios.getIos())
            {}

        }
    }
}

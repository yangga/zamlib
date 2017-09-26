//
// Created by SungWoo Yang on 2017. 9. 26..
//

#include "endPoint.h"

namespace zam {
    namespace net {
        namespace connection {

            std::string to_string(const endPoint& e) {
                std::stringstream ss;
                ss << "address:" << e.address
                   << ", port:" << e.port
                        ;
                return std::move(ss.str());
            }

        }
    }
}

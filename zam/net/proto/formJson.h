//
// Created by SungWoo Yang on 2017. 9. 24..
//

#ifndef ZAMLIB_FORMJSON_H
#define ZAMLIB_FORMJSON_H

#include <zam/net/net.h>

#include "../message/messageIStream.h"
#include "../message/messageOStream.h"

#include <json/value.h>
#include <json/writer.h>

namespace zam {
    namespace net {
        namespace proto {

            struct formJson {
                template <class PROTO_DATA_T>
                static constexpr bool check_value() { return std::is_base_of<Json::Value, PROTO_DATA_T>::value; }

                ZAMNET_API static void read(Json::Value& out, zam::net::messageIStream& is);

                ZAMNET_API static void write(zam::net::messageOStream& os, const Json::Value& data);
            };

        }
    }
}

#endif //ZAMLIB_FORMJSON_H

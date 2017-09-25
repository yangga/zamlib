//
// Created by SungWoo Yang on 2017. 9. 24..
//

#ifndef ZAMLIB_FORMPROTOBUF_H
#define ZAMLIB_FORMPROTOBUF_H

#include <zam/net/net.h>

#if ZAM_PROTOBUF_ENABLE == true

#include "../message/messageIStream.h"
#include "../message/messageOStream.h"

#include <google/protobuf/message.h>

namespace zam {
    namespace net {
        namespace proto {

            struct formProto {
                template <class PROTO_DATA_T>
                static constexpr bool check_value() { return std::is_base_of<google::protobuf::Message, PROTO_DATA_T>::value; }

                template <class PROTO_DATA_T>
                static void read(PROTO_DATA_T& out, zam::net::messageIStream& is) {
                    std::istream in(&is);
                    out.ParseFromIstream(&in);
                }

                template <class PROTO_DATA_T>
                static void write(zam::net::messageOStream& os, const PROTO_DATA_T& data) {
                    std::ostream o(&os);
                    data.SerializeToOstream(&o);
                }
            };

        }
    }
}

#endif  // ZAM_PROTOBUF_ENABLE == true

#endif //ZAMLIB_FORMPROTOBUF_H

//
// Created by SungWoo Yang on 2017. 9. 24..
//

#include "formJson.h"

namespace zam {
    namespace net {
        namespace proto {




            void formJson::write(zam::net::messageOStream& os, const Json::Value& data) {
#if JSONCPP_VERSION_MAJOR == 0
                Json::FastWriter writer;
                    os << writer.write(data);
#else
                Json::StreamWriterBuilder builder;
                std::unique_ptr<Json::StreamWriter> writer(
                        builder.newStreamWriter());
                std::ostream o(&os);
                writer->write(data, &o);
#endif
            }

        }
    }
}

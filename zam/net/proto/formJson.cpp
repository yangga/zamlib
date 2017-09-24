//
// Created by SungWoo Yang on 2017. 9. 24..
//

#include "formJson.h"

#include <json/reader.h>

namespace zam {
    namespace net {
        namespace proto {

            void formJson::read(Json::Value& out, zam::net::messageIStream& is) {
#if JSONCPP_VERSION_MAJOR == 0
                Json::Reader reader;
                reader.parse(is.current(), is.end(), out, false);
#else
                Json::CharReaderBuilder builder;
                std::unique_ptr<Json::CharReader> reader(
                        builder.newCharReader());
                reader->parse(is.current(), is.end(), &out, nullptr);
                is.readAll();
#endif
            }

            void formJson::write(zam::net::messageOStream& os, const Json::Value& data) {
#if JSONCPP_VERSION_MAJOR == 0
                Json::FastWriter writer;
                auto str = writer.write(data);
                os.write(str.c_str(), str.length());
#else
                Json::StreamWriterBuilder builder;
                builder["commentStyle"] = "None";
                builder["indentation"] = "";
                std::unique_ptr<Json::StreamWriter> writer(
                        builder.newStreamWriter());
                std::ostream o(&os);
                writer->write(data, &o);
#endif
            }

        }
    }
}

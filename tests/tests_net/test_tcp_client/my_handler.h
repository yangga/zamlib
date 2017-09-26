//
// Created by SungWoo Yang on 2017. 9. 21..
//

#ifndef ZAMLIB_MY_HANDLER_H
#define ZAMLIB_MY_HANDLER_H

#include <zam/net/handler/eventHandlerProtocolClient.h>

#include <zam/net/connection/connection.h>
#include <zam/net/message/message.h>

#include "../common/protocol_1.h"
#if ZAM_PROTOBUF_ENABLE == true
#include "../common/protocol_1_protobuf.pb.h"
#include "../common/protocol_1_protobuf.pb.cc"
#endif

namespace net = zam::net;
namespace connection = zam::net::connection;

class my_handler final : public zam::net::handler::eventHandlerProtocolClient
{
public:
    void onInitHandler() final {
        ZAM_LOGT("test1") << __FUNCTION__;
        registProtocol(s_c_json, &my_handler::onPackJson, this);
        registProtocol(s_c_struct, &my_handler::onPackStruct, this);
#if ZAM_PROTOBUF_ENABLE == true
        registProtocol(s_c_protobuf, &my_handler::onPackProtobuf, this);
#endif
    }

    void onConnect(boost::shared_ptr<connection::connection>& c) final {
        ZAM_LOGT("test1") << __FUNCTION__;

        /// sending json message
        Json::Value v;
        v["id"] = 2004;
        v["msg"] = "hello server~!";
        c->sendProtocol(c_s_json, v);

        /// sending structure message
        sample_struct_data d;
        d.a = 10;
        d.b = 20.2;
        d.c = 30.3;
        strncpy(d.d, "server", 6);
        c->sendProtocol(c_s_struct, d);

#if ZAM_PROTOBUF_ENABLE == true
        tutorial::LoginReq req;
        req.set_id("yangga0070@gmail.com");
        c->sendProtocol(c_s_protobuf, req);
#endif
    }

    void onConnectFailed(boost::shared_ptr<connection::connection>& c) final {
        ZAM_LOGT("test1") << __FUNCTION__;
    }

    void onClose(boost::shared_ptr<connection::connection>& c) final {
        ZAM_LOGT("test1") << __FUNCTION__;
    }

    void onExpired(boost::shared_ptr<connection::connection>& c) final {
        ZAM_LOGT("test1") << __FUNCTION__;
    }

private:
    void onPackJson(boost::shared_ptr<connection::connection> &c, const Json::Value& content) {
        ZAM_LOGD("test1") << __FUNCTION__ << ", " << content.toStyledString();
    }

    void onPackStruct(boost::shared_ptr<connection::connection> &c, const sample_struct_data& content) {
        ZAM_LOGD("test1") << __FUNCTION__ << ", " << content.d;
    }

#if ZAM_PROTOBUF_ENABLE == true
    void onPackProtobuf(boost::shared_ptr<connection::connection> &c, const tutorial::LoginAck& content) {
        ZAM_LOGD("test1") << __FUNCTION__ << ", " << content.name();
    }
#endif
};

#endif //ZAMLIB_MY_HANDLER_H

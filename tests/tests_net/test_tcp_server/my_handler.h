//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_MY_HANDLER_H
#define ZAMLIB_MY_HANDLER_H

#include <zam/net/handler/eventHandlerProtocolServer.h>

#include <zam/net/connection/connection.h>
#include <zam/net/message/message.h>

#include "../common/protocol_1.h"
#if ZAM_PROTOBUF_ENABLE == true
#include "../common/protocol_1_protobuf.pb.h"
#include "../common/protocol_1_protobuf.pb.cc"
#endif

namespace net = zam::net;
namespace connection = zam::net::connection;

class my_handler final : public zam::net::handler::eventHandlerProtocolServer
{
public:
    void onInitHandler() final {
        ZAM_LOGT("test1") << __FUNCTION__;
        registProtocol(c_s_json, &my_handler::onPackJson, this);
        registProtocol(c_s_struct, &my_handler::onPackStruct, this);
#if ZAM_PROTOBUF_ENABLE == true
        registProtocol(c_s_protobuf, &my_handler::onPackProtobuf, this);
#endif
    }

    void onAccept(boost::shared_ptr<connection::connection>& c) final {
        ZAM_LOGT("test1") << __FUNCTION__ << " - conn[" << zam::net::connection::to_string(c->remote_endpoint()) << "]";
    }

    void onClose(boost::shared_ptr<connection::connection>& c) final {
        ZAM_LOGT("test1") << __FUNCTION__ << " - conn[" << zam::net::connection::to_string(c->remote_endpoint()) << "]";
    }

    void onExpired(boost::shared_ptr<connection::connection>& c) final {
        ZAM_LOGT("test1") << __FUNCTION__ << " - conn[" << zam::net::connection::to_string(c->remote_endpoint()) << "]";
    }

private:
    void onPackJson(boost::shared_ptr<connection::connection> &c, const Json::Value& content) {
        ZAM_LOGT("test1") << __FUNCTION__ << " - conn[" << zam::net::connection::to_string(c->remote_endpoint()) << "]";
        ZAM_LOGD("test1") << content.toStyledString();

        /// sending json message
        Json::Value v;
        v["id"] = 1004;
        v["msg"] = "hello client~!";
        c->sendProtocol(s_c_json, v);
    }

    void onPackStruct(boost::shared_ptr<connection::connection> &c, const sample_struct_data& content) {
        ZAM_LOGT("test1") << __FUNCTION__ << " - conn[" << zam::net::connection::to_string(c->remote_endpoint()) << "]";
        ZAM_LOGD("test1") << content.a << ", " << content.b << ", " << content.c << ", " << content.d;

        /// sending structure message
        sample_struct_data d;
        d.a = 1;
        d.b = 2.2;
        d.c = 3.3;
        strncpy(d.d, "client", 6);
        c->sendProtocol(s_c_struct, d);
    }

#if ZAM_PROTOBUF_ENABLE == true
    void onPackProtobuf(boost::shared_ptr<connection::connection> &c, const tutorial::LoginReq& content) {
        ZAM_LOGT("test1") << __FUNCTION__ << " - conn[" << zam::net::connection::to_string(c->remote_endpoint()) << "]";
        ZAM_LOGD("test1") << content.id();

        tutorial::LoginAck ack;
        ack.set_name("Jake");
        ack.set_accno(1234567890);
        ack.set_money(9999999999);
        c->sendProtocol(s_c_protobuf, ack);
    }
#endif
};

#endif //ZAMLIB_MY_HANDLER_H

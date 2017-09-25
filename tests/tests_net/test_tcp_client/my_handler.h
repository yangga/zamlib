//
// Created by SungWoo Yang on 2017. 9. 21..
//

#ifndef ZAMLIB_MY_HANDLER_H
#define ZAMLIB_MY_HANDLER_H

#include <zam/net/handler/eventHandlerProtocolClient.h>

#include <zam/net/connection/connection.h>
#include <zam/net/message/message.h>

namespace net = zam::net;
namespace connection = zam::net::connection;

enum protocol : zam::net::protocol_t {
    protocol_json = 1000,
    protocol_struct = 1001
};

struct sample_struct_data {
    int a = 0;
    float b = 0;
    double c = 0;
    char d[80] = {0,};
};

class my_handler final : public zam::net::handler::eventHandlerProtocolClient
{
public:
    void onInitHandler() final {
        ZAM_LOGT("test1") << __FUNCTION__;
        registProtocol(protocol_json, &my_handler::onPackJson, this);
        registProtocol(protocol_struct, &my_handler::onPackStruct, this);
    }

    void onConnect(boost::shared_ptr<connection::connection>& c) final {
        ZAM_LOGT("test1") << __FUNCTION__;
    }

    void onConnectFailed(boost::shared_ptr<connection::connection>& c) final {
        ZAM_LOGT("test1") << __FUNCTION__;
    }

    void onClose(boost::shared_ptr<connection::connection>& c) final {
        ZAM_LOGT("test1") << __FUNCTION__;
    }

private:
    void onPackJson(boost::shared_ptr<connection::connection> &c, const Json::Value& content) {
        ZAM_LOGD("test1") << __FUNCTION__ << ", " << content.toStyledString();

        /// answering json message
        Json::Value v;
        v["id"] = 2004;
        v["msg"] = "hello server~!";
        c->sendProtocol(protocol_json, v);
    }

    void onPackStruct(boost::shared_ptr<connection::connection> &c, const sample_struct_data& content) {
        ZAM_LOGD("test1") << __FUNCTION__ << ", " << content.d;

        /// answering structure message
        sample_struct_data d;
        d.a = 10;
        d.b = 20.2;
        d.c = 30.3;
        strncpy(d.d, "server", 6);
        c->sendProtocol(protocol_struct, d);
    }
};

#endif //ZAMLIB_MY_HANDLER_H

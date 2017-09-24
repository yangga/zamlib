//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_MY_HANDLER_H
#define ZAMLIB_MY_HANDLER_H

#include <zam/net/handler/eventHandlerProtocol.h>

#include <zam/net/connection/connection.h>
#include <zam/net/message/message.h>

namespace net = zam::net;
namespace connection = zam::net::connection;

enum protocol : zam::net::protocol_t {
    protocol_json = 1000,
    protocol_struct = 1000
};

struct sample_struct_data {
    int a = 0;
    float b = 0;
    double c = 0;
    char d[80] = {0,};
};

class my_handler : public zam::net::handler::eventHandlerProtocol
{
public:
    void onInitHandler() override {
        ZAM_LOGT("test1") << __FUNCTION__;
        registProtocol(protocol_json, &my_handler::onPackJson, this);
        registProtocol(protocol_struct, &my_handler::onPackStruct, this);
    }

    void onAccept(boost::shared_ptr<connection::connection>& c) override {
        ZAM_LOGT("test1") << __FUNCTION__;

        /// sending json message
        Json::Value v;
        v["id"] = 1004;
        v["msg"] = "hello world~!";
        c->sendProtocol(protocol_json, v);

        /// sending structure message
        sample_struct_data d;
        d.a = 1;
        d.b = 2.2;
        d.c = 3.3;
        strncpy(d.d, "second structure data!", O_TRUNC);
        c->sendProtocol(protocol_struct, d);
    }

    void onConnect(boost::shared_ptr<connection::connection>& c) override {
        ZAM_LOGT("test1") << __FUNCTION__;
    }

    void onConnectFailed(boost::shared_ptr<connection::connection>& c) override {
        ZAM_LOGT("test1") << __FUNCTION__;
    }

    void onClose(boost::shared_ptr<connection::connection>& c) override {
        ZAM_LOGT("test1") << __FUNCTION__;
    }

    void onRecv(boost::shared_ptr<connection::connection> &c, boost::shared_ptr<net::message> &msg, size_t length) override {
        std::string data;
        net::messageIStream is(*msg, length);
        is >> data;
        ZAM_LOGD("test1") << __FUNCTION__ << ", recvdata:" << data;
    }

private:
    void onPackJson(boost::shared_ptr<connection::connection> &c, const Json::Value& content) {

    }

    void onPackStruct(boost::shared_ptr<connection::connection> &c, const sample_struct_data& content) {

    }
};

#endif //ZAMLIB_MY_HANDLER_H

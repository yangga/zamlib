//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_MY_HANDLER_H
#define ZAMLIB_MY_HANDLER_H

#include <zam/net/handler/eventHandler.h>

#include <zam/net/connection/connection.h>
#include <zam/net/message/message.h>

namespace net = zam::net;
namespace connection = zam::net::connection;

class my_handler : public zam::net::handler::eventHandler
{
public:
    void onAccept(boost::shared_ptr<connection::connection>& c) override {
        ZAM_LOGD("test1") << __FUNCTION__;
    }

    void onClose(boost::shared_ptr<connection::connection>& c) override {
        ZAM_LOGD("test1") << __FUNCTION__;
    }

    void onPacket(boost::shared_ptr<connection::connection>& c, boost::shared_ptr<net::message>& msg, size_t length) override {
        ZAM_LOGD("test1") << __FUNCTION__;
    }
};

#endif //ZAMLIB_MY_HANDLER_H
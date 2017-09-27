//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_EVENTHANDLER_H
#define ZAMLIB_EVENTHANDLER_H

#include <boost/enable_shared_from_this.hpp>

namespace zam {
    namespace net {

        namespace connection {
            class connection;
        }

        class message;

        namespace handler {

            struct eventHandler : public boost::enable_shared_from_this<eventHandler>
            {
                virtual void onInitHandler() = 0;
                virtual void onAccept(boost::shared_ptr<connection::connection>& c) = 0;
                virtual void onConnect(boost::shared_ptr<connection::connection>& c) = 0;
                virtual void onConnectFailed(boost::shared_ptr<connection::connection>& c) = 0;
                virtual void onClose(boost::shared_ptr<connection::connection>& c) = 0;
                virtual void onExpired(boost::shared_ptr<connection::connection>& c) = 0;
                virtual void onRecv(boost::shared_ptr<connection::connection> &c, boost::shared_ptr<message> &msg, size_t length) = 0;
            };

        }

        using eventHandler_ptr_t = boost::shared_ptr<handler::eventHandler>;
    }
}

#endif //ZAMLIB_EVENTHANDLER_H

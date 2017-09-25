//
// Created by SungWoo Yang on 2017. 9. 25..
//

#ifndef ZAMLIB_EVENTHANDLERPROTOCOLSERVER_H
#define ZAMLIB_EVENTHANDLERPROTOCOLSERVER_H

#include "eventHandlerProtocol.h"

namespace zam {
    namespace net {
        namespace handler {

            class eventHandlerProtocolServer : public eventHandlerProtocol
            {
            protected:
                eventHandlerProtocolServer() = default;

            private:
                void onConnect(boost::shared_ptr<connection::connection>& c) final {}
                void onConnectFailed(boost::shared_ptr<connection::connection>& c) final {}
            };

        }
    }
}

#endif //ZAMLIB_EVENTHANDLERPROTOCOLSERVER_H

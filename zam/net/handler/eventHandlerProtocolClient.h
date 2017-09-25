//
// Created by SungWoo Yang on 2017. 9. 25..
//

#ifndef ZAMLIB_EVENTHANDLERPROTOCOLCLIENT_H
#define ZAMLIB_EVENTHANDLERPROTOCOLCLIENT_H

#include "eventHandlerProtocol.h"

namespace zam {
    namespace net {
        namespace handler {

            class eventHandlerProtocolClient : public eventHandlerProtocol
            {
            protected:
                eventHandlerProtocolClient() = default;

            private:
                void onAccept(boost::shared_ptr<connection::connection>& c) final {}
            };

        }
    }
}

#endif //ZAMLIB_EVENTHANDLERPROTOCOLCLIENT_H

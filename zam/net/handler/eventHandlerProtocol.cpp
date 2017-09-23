//
// Created by yangga on 2017. 9. 23..
//

#include "eventHandlerProtocol.h"

#include "../message/messageIStream.h"

#include <zam/base/logger.h>

namespace zam {
    namespace net {
        namespace handler {

            void eventHandlerProtocol::onRecv(boost::shared_ptr<connection::connection> &c
                    , boost::shared_ptr<message> &msg
                    , size_t length) {

                messageIStream is(*msg, length);

                protocol_t proto(0);
                if (!is.readable(&proto, sizeof(proto))) {
                    ZAM_LOGD("default") << "packet is too short to read";
                    c->closing();
                    return;
                }

                auto itr = msgHandlerCont_.find(proto);
                if (msgHandlerCont_.end() == itr) {
                    ZAM_LOGD("default") << "invalid protocol - proto:" << proto;
                    c->closing();
                    return;
                }

                itr->second(c, msg, length);
            }

        }
    }
}

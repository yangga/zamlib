//
// Created by yangga on 2017. 9. 23..
//

#include "eventHandlerProtocol.h"

#include "../message/messageIStream.h"

#include <zam/base/logger.h>
#include <zam/base/exception.h>

namespace zam {
    namespace net {
        namespace handler {

            void eventHandlerProtocol::onRecv(boost::shared_ptr<connection::connection> &c
                    , boost::shared_ptr<message> &msg
                    , size_t length) {

                try {
                    messageIStream is(*msg, length);

                    protocol_t proto(0);
                    if (!is.readable(&proto, sizeof(proto))) {
                        throw base::zamException(netError::invalid_packet, "could not get proto number");
                    }

                    auto itr = msgHandlerCont_.find(proto);
                    if (msgHandlerCont_.end() == itr) {
                        throw base::zamException(netError::invalid_protocol, std::string("invalid protocol - proto:")+std::to_string(proto));
                    }

                    itr->second(c, msg, length);
                }
                catch(base::zamException& e) {
                    ZAM_LOGD("default") << "proto err - err:" << e.errorNo() << ", msg:" << e.what();
                    c->closing();
                }
                catch(std::exception& e) {
                    ZAM_LOGD("default") << "proto err - msg:" << e.what();
                    c->closing();
                }


            }

        }
    }
}

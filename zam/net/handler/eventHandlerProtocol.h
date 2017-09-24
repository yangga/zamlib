//
// Created by yangga on 2017. 9. 23..
//

#ifndef ZAMLIB_EVENTHANDLERPROTOCOL_H
#define ZAMLIB_EVENTHANDLERPROTOCOL_H

#include <zam/net/net.h>

#include "eventHandler.h"

#include "../connection/connection.h"

#include <json/value.h>

#include <map>

namespace zam {
    namespace net {
        namespace handler {

            class eventHandlerProtocol : public eventHandler {
            public:
                using msgHandlerDelegator = boost::function<void(connection_ptr_t&, boost::shared_ptr<message>&, size_t)>;

            protected:
                eventHandlerProtocol() = default;

            public:
                ZAMNET_API void onRecv(boost::shared_ptr<connection::connection> &c
                        , boost::shared_ptr<message> &msg
                        , size_t length) override;

            public:
                template <typename INSTANCE_TYPE, typename PROTOCOL_TYPE>
                bool registProtocol(protocol_t proto
                        , void(INSTANCE_TYPE::*method)(connection_ptr_t& conn, const PROTOCOL_TYPE& data)
                        , INSTANCE_TYPE* instance)
                {
                    std::cout << "registProtocol - type:" << "binary" << std::endl;
                    return true;
                }

                template <typename INSTANCE_TYPE>
                bool registProtocol(protocol_t proto
                        , void(INSTANCE_TYPE::*method)(connection_ptr_t& conn, const Json::Value& data)
                        , INSTANCE_TYPE* instance)
                {
                    std::cout << "registProtocol - type:" << "json" << std::endl;
                    return true;
                }

            private:
                std::map<protocol_t, msgHandlerDelegator> msgHandlerCont_;
            };

        }
    }
}

#endif //ZAMLIB_EVENTHANDLERPROTOCOL_H

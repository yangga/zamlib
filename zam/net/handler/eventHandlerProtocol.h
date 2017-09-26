//
// Created by yangga on 2017. 9. 23..
//

#ifndef ZAMLIB_EVENTHANDLERPROTOCOL_H
#define ZAMLIB_EVENTHANDLERPROTOCOL_H

#include <zam/net/net.h>

#include "eventHandler.h"

#include "../connection/connection.h"

#include <json/value.h>

#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <map>

namespace zam {
    namespace net {
        namespace handler {

            class eventHandlerProtocol : public eventHandler {
            public:
                using delegator_t = boost::function<void(connection_ptr_t&, boost::shared_ptr<message>&, size_t)>;

            protected:
                eventHandlerProtocol() = default;

                ZAMNET_API void onRecv(boost::shared_ptr<connection::connection> &c
                        , boost::shared_ptr<message> &msg
                        , size_t length) override;

            public:
                template <typename INSTANCE_TYPE, typename PROTOCOL_TYPE>
                bool registProtocol(protocol_t proto
                        , void(INSTANCE_TYPE::*method)(connection_ptr_t& conn, PROTOCOL_TYPE data)
                        , INSTANCE_TYPE* instance)
                {
                    static_assert(std::is_member_function_pointer<decltype(method)>::value, "it's not a member function proto handler");

                    auto ll = [method, instance](connection_ptr_t& c, boost::shared_ptr<message>& msg, size_t length) {
                        using type = std::remove_const_t< std::remove_reference_t<PROTOCOL_TYPE> >;

                        messageIStream is(*msg, length);
                        is.skip(sizeof(protocol_t));
                        type parsedData;
                        proto::proto_form_factory_impl<type>::type::read(parsedData, is);
                        (instance->*method)(c, parsedData);
                    };

                    using namespace boost::placeholders;
                    return registProtocol(proto, boost::bind<void>(ll, _1, _2, _3));
                }

                template <typename PROTOCOL_TYPE>
                bool registProtocol(protocol_t proto
                        , void(*fn)(connection_ptr_t&, PROTOCOL_TYPE))
                {
                    static_assert(false == std::is_member_function_pointer<decltype(fn)>::value, "it's not a static function proto handler");

                    auto ll = [fn](connection_ptr_t& c, boost::shared_ptr<message>& msg, size_t length) {
                        using type = std::remove_const_t< std::remove_reference_t<PROTOCOL_TYPE> >;

                        messageIStream is(*msg, length);
                        is.skip(sizeof(protocol_t));
                        type parsedData;
                        proto::proto_form_factory_impl<type>::type::read(parsedData, is);
                        fn(c, parsedData);
                    };

                    using namespace boost::placeholders;
                    return registProtocol(proto, boost::bind<void>(ll, _1, _2, _3));
                }

                ZAMNET_API bool registProtocol(protocol_t proto, delegator_t fn);

            private:
                std::map<protocol_t, delegator_t> msgHandlerCont_;
            };

        }
    }
}

#endif //ZAMLIB_EVENTHANDLERPROTOCOL_H

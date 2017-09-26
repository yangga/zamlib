//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_EVENTDISPATCHER_H
#define ZAMLIB_EVENTDISPATCHER_H

#include "eventHandler.h"

#include <zam/base/io/ioObject.h>

#include <boost/bind.hpp>
#include <type_traits>

namespace zam {
    namespace net {
        namespace handler {

            template <class EVENT_HANDLER>
            class eventDispatcherSingleThread final
                    : public base::io::ioObject
                    , public eventHandler
            {
                static_assert(std::is_base_of<eventHandler, EVENT_HANDLER>::value, "you have to use eventHandler");

            public:
                using eventHandler_t = EVENT_HANDLER;

                explicit eventDispatcherSingleThread(base::io::ioSystem& ios)
                        : base::io::ioObject(ios)
                        , handler_(boost::make_shared<eventHandler_t>())
                {}

                boost::shared_ptr<eventHandler_t>& handlerReal() { return handler_; }

            public:
                void onInitHandler() final {
                    ioPost(boost::bind(&eventHandler::onInitHandler, handler_));
                }
                void onAccept(boost::shared_ptr<connection::connection>& c) final {
                    ioPost(boost::bind(&eventHandler::onAccept, handler_, c));
                }

                void onConnect(boost::shared_ptr<connection::connection>& c) final {
                    ioPost(boost::bind(&eventHandler::onConnect, handler_, c));
                }

                void onConnectFailed(boost::shared_ptr<connection::connection>& c) final {
                    ioPost(boost::bind(&eventHandler::onConnectFailed, handler_, c));
                }

                void onClose(boost::shared_ptr<connection::connection>& c) final {
                    ioPost(boost::bind(&eventHandler::onClose, handler_, c));
                }

                void onRecv(boost::shared_ptr<connection::connection> &c, boost::shared_ptr<message> &msg, size_t length) final {
                    ioPost(boost::bind(&eventHandler::onRecv, handler_, c, msg, length));
                }

            private:
                boost::shared_ptr<eventHandler_t> handler_;
            };

        }
    }
}

#endif //ZAMLIB_EVENTDISPATCHER_H

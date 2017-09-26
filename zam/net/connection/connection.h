//
// Created by SungWoo Yang on 2017. 9. 19..
//

#ifndef ZAMLIB_CONNECTION_H
#define ZAMLIB_CONNECTION_H

#include <zam/net/net.h>

#include "endPoint.h"

#include "../message/messageOStream.h"
#include "../warehouse/warehouse.h"

#include "../proto/forms.h"

#include <zam/base/io/ioObject.h>
#include <zam/base/schedule/scheduler.h>

#include <boost/enable_shared_from_this.hpp>

namespace Json {
    class Value;
}

namespace google {
    namespace protobuf {
        class Message;
    }
}

namespace zam {
    namespace net {
        namespace warehouse {
            struct warehouse;
        }

        namespace connection {

            class connection
                : public base::io::ioObject
                , public boost::enable_shared_from_this<connection>
            {
            public:
                enum class status : unsigned char {
                    open = 0,
                    closing = 1,
                    close = 2,
                };

                virtual endPoint remote_endpoint() = 0;
                virtual void startAccept() = 0;
                virtual void startConnect() = 0;
                virtual void closing() = 0;
                virtual void send(message& msg, size_t msg_len) = 0;
                virtual void sendRaw(void* src, size_t src_len) = 0;

            public:
                ZAMNET_API void initialize(warehouse::warehouse& wh);

                cipher_ptr_t& cipher() { return cipher_; }
                eventHandler_ptr_t& eventHandler() { return evtHandler_; }
                packer_ptr_t& packer() { return packer_; }

                inline void send(messageOStream const& os) {
                    send(os.buf(), os.dataSize());
                }

                template <typename PROTO_DATA_T>
                void sendProtocol(protocol_t proto, const PROTO_DATA_T& data);

                template <class CHILD_CONNECTION>
                CHILD_CONNECTION& toChild();

                zam::base::schedule::scheduler& scheduler() const { return *scheduler_; }

            protected:
                ZAMNET_API explicit connection(base::io::ioSystem& ios);

                cipher_ptr_t cipher_;
                eventHandler_ptr_t evtHandler_;
                packer_ptr_t packer_;

                boost::shared_ptr<zam::base::schedule::scheduler> scheduler_;
            };



            template <typename PROTO_DATA_T>
            void connection::sendProtocol(protocol_t proto, const PROTO_DATA_T& data) {
                message msg;
                messageOStream os(msg);

                os << proto;

                proto::proto_form_factory_impl<PROTO_DATA_T>::type::write(os, data);
                send(os);
            }

            template <class CHILD_CONNECTION>
            CHILD_CONNECTION& connection::toChild() {
                static_assert(std::is_base_of<connection, CHILD_CONNECTION>::value, "child connection must be child of connection");
                return dynamic_cast<CHILD_CONNECTION&>(*this);
            }
        }


        using connection_ptr_t = boost::shared_ptr<connection::connection>;
    }
}

#endif //ZAMLIB_CONNECTION_H

//
// Created by yangga on 2017. 9. 18..
//

#include "packerDefault.h"

#include "../message/messageIStream.h"
#include "../message/messageOStream.h"

#include <zam/base/exception.h>
#include <zam/net/netError.h>

namespace zam {
    namespace net {
        namespace packer {

            constexpr uint16_t PACKER_DEFAULT_ID = 0xffff;

#pragma pack(1)
            struct PACKER_DEFAULT_HEADER
            {
                uint16_t key;
                uint16_t length;
            };
#pragma pack()

            size_t packerDefault::pack(message& out, messageIStream& is)
            {
                messageOStream os(out);
                os << PACKER_DEFAULT_HEADER{PACKER_DEFAULT_ID, static_cast<uint16_t>(is.dataSize())};

                if (!os.writable(is.dataSize()))
                    throw base::zamException(netError::overflow, "input message is too large");

                os.write(is.buf().ptr(), is.dataSize());
                return os.dataSize();
            }

            size_t packerDefault::unpack(message& out, messageIStream& is)
            {
                PACKER_DEFAULT_HEADER header{0,};
                if (sizeof(header) != is.read(&header, sizeof(header)))
                    throw base::zamException(netError::incompleted_packet, "input message is too short");

                if (header.key != PACKER_DEFAULT_ID
                    || message::size_v < (header.length + sizeof(header)))
                    throw base::zamException(netError::invalid_packet, "invalid packet");

                if (!is.readable(header.length))
                    throw base::zamException(netError::incompleted_packet, "receive incompleted");

                messageOStream os(out);
                if (header.length != os.write(is.current(), header.length))
                    throw base::zamException(netError::overflow, "failed to write large message");

                is.skip(header.length);

                return os.dataSize();
            }

        }
    }
}

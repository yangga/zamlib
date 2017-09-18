//
// Created by SungWoo Yang on 2017. 9. 18..
//

#ifndef ZAMLIB_STREAMOUTPUTBUF_H
#define ZAMLIB_STREAMOUTPUTBUF_H

#include <streambuf>

#include <boost/smart_ptr.hpp>

#include <memory>

namespace zam {
    namespace base {
        namespace stream {

            template <class BUFFER>
            class streamInputBuf;

            template <class BUFFER>
            class streamOutputBuf : std::streambuf {
                friend class streamInputBuf<BUFFER>;

            public:
                using buffer_t = BUFFER;

            public:
                explicit streamOutputBuf(buffer_t& buf, size_t offset=0);
                explicit streamOutputBuf(streamInputBuf<BUFFER>& streamOutBuf);

                inline buffer_t& buf() const BOOST_NOEXCEPT { return buf_; }

                inline char* begin() const BOOST_NOEXCEPT { return pbase(); }
                inline char* current() const BOOST_NOEXCEPT { return pptr(); }
                inline char* end() const BOOST_NOEXCEPT { return epptr(); }

                size_t sizeBuffer() const BOOST_NOEXCEPT { return BUFFER::size_v; }
                size_t sizeData() const BOOST_NOEXCEPT { return current()-begin(); }
                size_t sizeLeft() const BOOST_NOEXCEPT { return end()-current(); }

                size_t write(const char* src, size_t count);

                void skip(size_t count);

            private:
                buffer_t& buf_;
            };

            template <class BUFFER>
            streamOutputBuf<BUFFER>::streamOutputBuf(buffer_t& buf, size_t offset)
                : buf_(buf)
            {
                assert(offset <= BUFFER::size_v && "offset must be smaller than buffer size");
                this->setp(buf_.ptr(), buf_.ptr()+sizeBuffer());
                skip(offset);
            }

            template <class BUFFER>
            streamOutputBuf<BUFFER>::streamOutputBuf(streamInputBuf<BUFFER>& streamOutBuf)
                : buf_(streamOutBuf.buf_)
            {
                this->setp(buf_.ptr(), buf_.ptr()+sizeBuffer());
                skip(streamOutBuf.sizeData());
            }

            template <class BUFFER>
            size_t streamOutputBuf<BUFFER>::write(const char* src, size_t count) {
                return static_cast<size_t>(sputn(src, count));
            }

            template <class BUFFER>
            void streamOutputBuf<BUFFER>::skip(size_t count) {
                pbump(static_cast<int>(count));
            }

        }
    }
}

#endif //ZAMLIB_STREAMOUTPUTBUF_H

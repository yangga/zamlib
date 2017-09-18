//
// Created by SungWoo Yang on 2017. 9. 18..
//

#ifndef ZAMLIB_STREAMBUF_H
#define ZAMLIB_STREAMBUF_H

#include <streambuf>

#include <boost/smart_ptr.hpp>

#include <memory>

namespace zam {
    namespace base {
        namespace stream {

            template <class BUFFER>
            class streamOutputBuf;

            template <class BUFFER>
            class streamInputBuf : std::streambuf
            {
                friend class streamOutputBuf<BUFFER>;

            public:
                using buffer_t = BUFFER;


            public:
                explicit streamInputBuf(buffer_t& buf, size_t sizeData);
                explicit streamInputBuf(streamOutputBuf<BUFFER>& streamOutBuf);

                inline buffer_t& buf() const BOOST_NOEXCEPT { return buf_; }

                inline char* begin() const BOOST_NOEXCEPT { return eback(); }
                inline char* current() const BOOST_NOEXCEPT { return gptr(); }
                inline char* end() const BOOST_NOEXCEPT { return egptr(); }

                size_t sizeBuffer() const BOOST_NOEXCEPT { return BUFFER::size_v; }
                size_t sizeData() const BOOST_NOEXCEPT { return end()-begin(); }
                size_t sizeLeft() const BOOST_NOEXCEPT { return end()-current(); }

                size_t read(char* dst, size_t count);
                size_t readAll();

                void skip(size_t count);

            private:
                buffer_t& buf_;
            };

            template <class BUFFER>
            streamInputBuf<BUFFER>::streamInputBuf(buffer_t& buf, size_t sizeData)
                : buf_(buf)
            {
                assert(sizeData <= BUFFER::size_v && "data must be lesser than buffer size");
                setg(buf_.ptr(), buf_.ptr(), buf_.ptr() + sizeData);
            }

            template <class BUFFER>
            streamInputBuf<BUFFER>::streamInputBuf(streamOutputBuf<BUFFER>& streamOutBuf)
                    : buf_(streamOutBuf.buf_)
            {
                setg(buf_.ptr(), buf_.ptr(), buf_.ptr() + streamOutBuf.sizeData());
            }

            template <class BUFFER>
            size_t streamInputBuf<BUFFER>::read(char* dst, size_t count) {
                return static_cast<size_t>(sgetn(dst, count));
            }

            template <class BUFFER>
            size_t streamInputBuf<BUFFER>::readAll() {
                const auto leftLen = sizeLeft();
                skip(sizeLeft());
                return leftLen;
            }

            template <class BUFFER>
            void streamInputBuf<BUFFER>::skip(size_t count) {
                gbump(static_cast<int>(count));
            }


        }
    }
}

#endif //ZAMLIB_STREAMBUF_H

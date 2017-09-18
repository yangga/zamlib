//
// Created by SungWoo Yang on 2017. 9. 18..
//

#ifndef ZAMLIB_STREAMBUF_H
#define ZAMLIB_STREAMBUF_H

#include <streambuf>

#include <boost/smart_ptr.hpp>

#include <memory>
#include <string>
#include <vector>

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

                inline constexpr size_t bufferSize() const BOOST_NOEXCEPT { return BUFFER::size_v; }

                inline char* begin() const BOOST_NOEXCEPT { return eback(); }
                inline char* current() const BOOST_NOEXCEPT { return gptr(); }
                inline char* end() const BOOST_NOEXCEPT { return egptr(); }

                inline size_t dataSize() const BOOST_NOEXCEPT { return end()-begin(); }

                size_t read(void* dst, size_t count);
                size_t readAll();

                bool readable(void* dst, size_t count) const;
                inline bool readable(size_t count) const BOOST_NOEXCEPT;
                inline size_t readableSize() const BOOST_NOEXCEPT { return end()-current(); }

                void skip(size_t count);

                template< typename T >
                inline streamInputBuf<BUFFER>& operator >> (T& b);

                template< typename T >
                inline streamInputBuf<BUFFER>& operator >> (std::vector<T>& b);

                inline streamInputBuf<BUFFER>& operator >> (std::string& b);

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
                setg(buf_.ptr(), buf_.ptr(), buf_.ptr() + streamOutBuf.dataSize());
            }

            template <class BUFFER>
            size_t streamInputBuf<BUFFER>::read(void* dst, size_t count) {
                return static_cast<size_t>(sgetn((char*)dst, count));
            }

            template <class BUFFER>
            size_t streamInputBuf<BUFFER>::readAll() {
                const auto leftLen = readableSize();
                skip(readableSize());
                return leftLen;
            }

            template <class BUFFER>
            bool streamInputBuf<BUFFER>::readable(void* dst, size_t count) const {
                if (!readable(count))
                    return false;

                memcpy(dst, current(), count);
                return true;
            }

            template <class BUFFER>
            bool streamInputBuf<BUFFER>::readable(size_t count) const BOOST_NOEXCEPT {
                return (count <= readableSize());
            }

            template <class BUFFER>
            void streamInputBuf<BUFFER>::skip(size_t count) {
                gbump(static_cast<int>(count));
            }


            template <class BUFFER>
            template< typename T >
            streamInputBuf<BUFFER>& streamInputBuf<BUFFER>::operator >> (T& b) {
                read((char*)&b, sizeof(b));
                return *this;
            }

            template <class BUFFER>
            template< typename T >
            streamInputBuf<BUFFER>& streamInputBuf<BUFFER>::operator >> (std::vector<T>& b) {
                uint16_t size;
                (*this) >> size;
                b.reserve(size);
                b.resize(0);

                for (size_t i = 0; i < size; ++i)
                {
                    T e;
                    (*this) >> e;
                    b.push_back(std::move(e));
                }
                return *this;
            }

            template <class BUFFER>
            streamInputBuf<BUFFER>& streamInputBuf<BUFFER>::operator >> (std::string& b) {
                uint16_t size;
                (*this) >> size;
                if (0 < size)
                {
                    b.assign(current(), size);
                    skip(size * sizeof(char));
                }

                return *this;
            }


        }
    }
}

#endif //ZAMLIB_STREAMBUF_H

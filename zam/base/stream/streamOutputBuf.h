//
// Created by SungWoo Yang on 2017. 9. 18..
//

#ifndef ZAMLIB_STREAMOUTPUTBUF_H
#define ZAMLIB_STREAMOUTPUTBUF_H

#include <streambuf>

#include <boost/smart_ptr.hpp>

#include <memory>
#include <string>
#include <vector>

namespace zam {
    namespace base {
        namespace stream {

            template <class BUFFER>
            class streamInputBuf;

            template <class BUFFER>
            class streamOutputBuf : public std::streambuf {
                friend class streamInputBuf<BUFFER>;

            public:
                using buffer_t = BUFFER;

            public:
                explicit streamOutputBuf(buffer_t& buf, size_t offset=0);
                explicit streamOutputBuf(streamInputBuf<BUFFER>& streamOutBuf);

                inline buffer_t& buf() const BOOST_NOEXCEPT { return buf_; }

                inline constexpr size_t bufferSize() const BOOST_NOEXCEPT { return BUFFER::size_v; }

                inline char* begin() const BOOST_NOEXCEPT { return pbase(); }
                inline char* current() const BOOST_NOEXCEPT { return pptr(); }
                inline char* end() const BOOST_NOEXCEPT { return epptr(); }

                inline size_t dataSize() const BOOST_NOEXCEPT { return current()-begin(); }

                size_t write(const char* src, size_t size);

                inline bool writable(size_t size) const;
                inline size_t writableSize() const BOOST_NOEXCEPT { return end()-current(); }

                void skip(size_t size);

                template< typename T >
                inline streamOutputBuf<BUFFER>& operator << (const T& b);

                template< typename T >
                inline streamOutputBuf<BUFFER>& operator << (T&& b);

                template< typename T >
                inline streamOutputBuf<BUFFER>& operator << (const std::vector<T>& b);

                template< typename T >
                inline streamOutputBuf<BUFFER>& operator << (std::vector<T>&& b);

                inline streamOutputBuf<BUFFER>& operator << (const std::string& b);
                inline streamOutputBuf<BUFFER>& operator << (std::string&& b);

            private:
                buffer_t& buf_;
            };

            template <class BUFFER>
            streamOutputBuf<BUFFER>::streamOutputBuf(buffer_t& buf, size_t offset)
                : buf_(buf)
            {
                assert(offset <= BUFFER::size_v && "offset must be smaller than buffer size");
                this->setp(buf_.ptr(), buf_.ptr()+ bufferSize());
                skip(offset);
            }

            template <class BUFFER>
            streamOutputBuf<BUFFER>::streamOutputBuf(streamInputBuf<BUFFER>& streamOutBuf)
                : buf_(streamOutBuf.buf_)
            {
                this->setp(buf_.ptr(), buf_.ptr()+ bufferSize());
                skip(streamOutBuf.dataSize());
            }

            template <class BUFFER>
            size_t streamOutputBuf<BUFFER>::write(const char* src, size_t size) {
                return static_cast<size_t>(sputn(src, size));
            }

            template <class BUFFER>
            bool streamOutputBuf<BUFFER>::writable(size_t size) const {
                return (size <= writableSize());
            }

            template <class BUFFER>
            void streamOutputBuf<BUFFER>::skip(size_t size) {
                pbump(static_cast<int>(size));
            }


            template <class BUFFER>
            template< typename T >
            streamOutputBuf<BUFFER>& streamOutputBuf<BUFFER>::operator << (const T& b) {
                write((char*)&b, sizeof(b));
                return *this;
            }

            template <class BUFFER>
            template< typename T >
            streamOutputBuf<BUFFER>& streamOutputBuf<BUFFER>::operator << (T&& b) {
                write((char*)&b, sizeof(b));
                return *this;
            }

            template <class BUFFER>
            template< typename T >
            streamOutputBuf<BUFFER>& streamOutputBuf<BUFFER>::operator << (const std::vector<T>& b) {
                (*this) << static_cast<uint16_t>(b.size());

                for (auto& d : b)
                    (void)((*this) << d);

                return *this;
            }

            template <class BUFFER>
            template< typename T >
            streamOutputBuf<BUFFER>& streamOutputBuf<BUFFER>::operator << (std::vector<T>&& b) {
                return operator <<((const std::vector<T>&)b);
            }

            template <class BUFFER>
            streamOutputBuf<BUFFER>& streamOutputBuf<BUFFER>::operator << (const std::string& b)
            {
                const auto size = static_cast<uint16_t>(b.length());
                (*this) << size;
                if (0 < size) {
                    write(b.c_str(), b.length() * sizeof(char));
                }

                return *this;
            }

            template <class BUFFER>
            streamOutputBuf<BUFFER>& streamOutputBuf<BUFFER>::operator << (std::string&& b)
            {
                return operator<<((const std::string&)b);
            }

        }
    }
}

#endif //ZAMLIB_STREAMOUTPUTBUF_H

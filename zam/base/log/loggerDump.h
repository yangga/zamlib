//
// Created by SungWoo Yang on 2017. 9. 27..
//

#ifndef ZAMLIB_LOGGERDUMPER_H
#define ZAMLIB_LOGGERDUMPER_H

#include <zam/base/base.h>

#include <boost/format.hpp>
#include <boost/log/utility/manipulators/dump.hpp>

#include <string>

#define ZAM_DUMP            zam::base::log::dump_pretty
#define ZAM_DUMP_INLINE     zam::base::log::dump_inline

namespace zam {
    namespace base {
        namespace log {

            class dump_manip_pretty
            {
            private:
                const char* m_data;
                std::size_t m_size;

            public:
                dump_manip_pretty(const void* data, std::size_t size) BOOST_NOEXCEPT : m_data((const char*)data), m_size(size) {}
                dump_manip_pretty(dump_manip_pretty const& that) BOOST_NOEXCEPT = default;

                const char* get_data() const BOOST_NOEXCEPT { return m_data; }
                std::size_t get_size() const BOOST_NOEXCEPT { return m_size; }
            };

            class dump_manip_pretty_bounded :
                    public dump_manip_pretty
            {
            private:
                //! Maximum size to output, in bytes
                std::size_t m_max_size;

            public:
                dump_manip_pretty_bounded(const void* data, std::size_t size, std::size_t max_size) BOOST_NOEXCEPT : dump_manip_pretty(data, size), m_max_size(max_size) {}
                dump_manip_pretty_bounded(dump_manip_pretty_bounded const& that) BOOST_NOEXCEPT : dump_manip_pretty(static_cast< dump_manip_pretty const& >(that)), m_max_size(that.m_max_size) {}

                std::size_t get_max_size() const BOOST_NOEXCEPT { return m_max_size; }
            };

            using dump_manip_inline = boost::log::dump_manip;
            using dump_manip_inline_bounded = boost::log::bounded_dump_manip;

            ZAMBASE_API dump_manip_pretty dump_pretty(void* data, size_t data_len);
            ZAMBASE_API dump_manip_pretty_bounded dump_pretty(void* data, size_t data_len, size_t max_len);

            ZAMBASE_API dump_manip_inline dump_inline(void* data, size_t data_len);
            ZAMBASE_API dump_manip_inline_bounded dump_inline(void* data, size_t data_len, size_t max_len);




            template< typename CharT, typename TraitsT >
            inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, dump_manip_pretty const& manip)
            {
                if (!strm.good())
                    return strm;

                constexpr size_t bytes_per_line = 16;
                auto begin = manip.get_data();
                auto end = manip.get_data() + manip.get_size();

                for (auto line = begin; line < end; line += bytes_per_line) {
                    strm << std::endl;
                    const size_t len_this = (end - line) >= bytes_per_line ? bytes_per_line : (end - line) % bytes_per_line;
                    strm << boost::format("%08lX: ") % (size_t)line;

                    // left side (hexa)
                    for (size_t i=0; i<bytes_per_line; ++i) {
                        if (i == 8)
                            strm << " ";

                        if (i < len_this) {
                            strm << boost::format("%02X ") % ((int)*(line + i));
                        }
                        else {
                            strm << "?? ";
                        }
                    }

                    strm << " ";

                    // right side (text)
                    for (size_t i=0; i<bytes_per_line; ++i) {
                        if (i == 8)
                            strm << " ";

                        if (i < len_this) {
                            const char c = *(line + i);
                            strm << boost::format("%c") % (unsigned char)((isprint(c) ? c : ('.')));
                        }
                        else {
                            strm << " ";
                        }
                    }
                }

                return strm;
            }

            //! The operator outputs binary data to a stream
            template< typename CharT, typename TraitsT >
            inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, dump_manip_pretty_bounded const& manip)
            {
                if (!strm.good())
                    return strm;

                dump_manip_pretty m2(manip.get_data(), (std::min)(manip.get_size(), manip.get_max_size()));
                strm << m2;

                if (manip.get_max_size() < manip.get_size()) {
                    strm << std::endl << "and " << (manip.get_size() - manip.get_max_size()) << " bytes more";
                }

                return strm;
            }
        }
    }
}

#endif //ZAMLIB_LOGGERDUMPER_H

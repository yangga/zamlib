//
// Created by SungWoo Yang on 2017. 9. 18..
//

#ifndef ZAMLIB_BUFFER_H
#define ZAMLIB_BUFFER_H

#include <zam/base/base.h>

#include <array>

namespace zam {
    namespace base {

        template <size_t SIZE>
        class buffer
        {
        public:
            static constexpr size_t size_v = SIZE;

        public:
            inline char* ptr() { return &buf_.front(); }
            inline const char* const ptr() const { return &buf_.front(); }

            inline constexpr size_t size() const BOOST_NOEXCEPT { return size_v; }

        protected:
            std::array<char, SIZE> buf_ = {0,};
        };

    }
}

#endif //ZAMLIB_BUFFER_H

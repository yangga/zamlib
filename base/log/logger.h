//
// Created by SungWoo Yang on 2017. 8. 30..
//

#ifndef ZAM_LOG_H
#define ZAM_LOG_H

#include "loggerDefine.h"

#include "loggerInitializer.h"

#include "detail/logWriter.h"

#include <sstream>

namespace zam {
    namespace base {
        namespace log {

            class logWriter;
            class loggerInitializer;

            class logger {
                friend class loggerInitializer;

            public:
                logger() = default;
                ~logger();

                bool operator! () const BOOST_NOEXCEPT {
                    return (nullptr != writer_);
                }

                template <typename T>
                logger& operator << (T const& v) {
                    if (!writer_->checkLevel(lv_))
                        return *this;

                    ss_ << v;
                    return *this;
                }

                logger& operator << (int8_t const& v) {
                    return operator<<(static_cast<const int32_t>(v));
                }

                logger& operator << (uint8_t const& v) {
                    return operator<<(static_cast<const uint32_t>(v));
                }


            private:
                void flush();

            private:
                level lv_ = level::info;
                logWriter* writer_ = nullptr;
                std::stringstream ss_;
            };

        }   // namespace log
    }   // namespace base
}  // namespace zam

#define __logging_macro__(_TAG_, _LEVEL_)  for (zam::base::log::logger _logger;!!_logger;) \
                                               loggerInitializer::initializeLogger(_logger, _TAG_, _LEVEL_)

#define logt(_TAG_) __logging_macro__(_TAG_, zam::base::log::level::trace)
#define logd(_TAG_) __logging_macro__(_TAG_, zam::base::log::level::debug)
#define logi(_TAG_) __logging_macro__(_TAG_, zam::base::log::level::info)
#define logw(_TAG_) __logging_macro__(_TAG_, zam::base::log::level::warn)
#define loge(_TAG_) __logging_macro__(_TAG_, zam::base::log::level::error)
#define logf(_TAG_) __logging_macro__(_TAG_, zam::base::log::level::fatal)


#endif //ZAM_LOG_H

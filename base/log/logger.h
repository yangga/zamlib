//
// Created by SungWoo Yang on 2017. 8. 30..
//

#ifndef ZAM_BASE_LOG_LOGGER_H
#define ZAM_BASE_LOG_LOGGER_H

#include "loggerDefine.h"

#include "detail/loggerInitializer.h"
#include "base/log/detail/loggerWriter.h"

#include <sstream>


namespace zam {
    namespace base {
        namespace log {

            class loggerWriter;
            class loggerInitializer;

            class logger {
                friend class loggerInitializer;

            public:
                logger() = default;
                logger(const logger&) = delete;
                logger(logger&&) = delete;
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

                logger& operator=(const logger&) = delete;
                logger&& operator=(logger&&) = delete;

            private:
                void flush();

            private:
                level lv_ = level::all;
                loggerWriter* writer_ = nullptr;
                std::stringstream ss_ = std::stringstream();
            };



        }   // namespace log
    }   // namespace base
}  // namespace zam

#define ZAM_LOGGING_MACRO(_TAG_, _LEVEL_)  for (zam::base::log::logger _logger;!!_logger;) \
                                               loggerInitializer::initializeLogger(_logger, _TAG_, _LEVEL_)

#define ZAM_LOGT(_TAG_) ZAM_LOGGING_MACRO(_TAG_, zam::base::log::level::trace)
#define ZAM_LOGD(_TAG_) ZAM_LOGGING_MACRO(_TAG_, zam::base::log::level::debug)
#define ZAM_LOGI(_TAG_) ZAM_LOGGING_MACRO(_TAG_, zam::base::log::level::info)
#define ZAM_LOGW(_TAG_) ZAM_LOGGING_MACRO(_TAG_, zam::base::log::level::warn)
#define ZAM_LOGE(_TAG_) ZAM_LOGGING_MACRO(_TAG_, zam::base::log::level::error)
#define ZAM_LOGF(_TAG_) ZAM_LOGGING_MACRO(_TAG_, zam::base::log::level::fatal)

#endif //ZAM_BASE_LOG_LOGGER_H

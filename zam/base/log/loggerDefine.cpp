//
// Created by SungWoo Yang on 2017. 9. 1..
//

#include "loggerDefine.h"

#include<boost/tokenizer.hpp>

#include <sstream>

namespace zam {
    namespace base {
        namespace log {

            /// level
            struct __tagLevelInfo__{
                level lv;
                const char* name;
                const char* initial;
                const char* display;
            } __logLevelDic__ [] = {
                    {level::trace, "trace", "t", "trace"},
                    {level::debug, "debug", "d", "debug"},
                    {level::info,  "info",  "i", "info "},
                    {level::warn,  "warn",  "w", "warn "},
                    {level::error, "error", "e", "error"},
                    {level::fatal, "fatal", "f", "fatal"}
            };

            const char* toString(level lv) {
                for (auto const& dic : __logLevelDic__) {
                    if (dic.lv == lv)
                        return dic.name;
                }

                return "unknown";
            }

            level toLevel(const char* name) {
                if (nullptr == name || 0 == strlen(name))
                    throw std::invalid_argument("invalid level type");

                std::string lname(name);
                std::transform(lname.begin(), lname.end(), lname.begin(), ::tolower);

                for (auto const& dic : __logLevelDic__) {
                    if (lname == dic.name)
                        return dic.lv;
                }

                for (auto const& dic : __logLevelDic__) {
                    if (lname == dic.initial)
                        return dic.lv;
                }

                return __logLevelDic__[0].lv;
            }

            std::ostream& operator << (std::ostream& strm, level lv) {
                strm << __logLevelDic__[lv].display;
                return strm;
            }

            /// stream
            struct {
                streamType type;
                const char* name;
                const char* initial;
            } __streamTypeDic__ [] = {
                    {streamType::console, "console", "c"},
                    {streamType::file,    "file",    "f"},
                    {streamType::tracer,  "tracer",  "t"},
                    {streamType::syslog,  "syslog",  "s"},
                    {streamType::udp,     "udp",     "u"}
            };

            const char* toString(streamType type) {
                for (auto const& dic : __streamTypeDic__) {
                    if (dic.type == type)
                        return dic.name;
                }

                return "unknown";
            }

            streamType toStreamType(const char *name) {
                if (nullptr == name || 0 == strlen(name))
                    throw std::invalid_argument("invalid stream type");

                std::string lname(name);
                std::transform(lname.begin(), lname.end(), lname.begin(), ::tolower);

                for (auto const& dic : __streamTypeDic__) {
                    if (lname == dic.name)
                        return dic.type;
                }

                for (auto const& dic : __streamTypeDic__) {
                    if (lname == dic.initial)
                        return dic.type;
                }

                return __streamTypeDic__[0].type;
            }


            /// format
            struct {
                formatType type;
                const char* name;
                const char* initial;
            } __formatTypeDic__ [] = {
                    {formatType::plain,    "plain",     "n"},
                    {formatType::xml,       "xml",      "x"},
                    {formatType::json,      "json",     "j"}
            };

            const char* toString(formatType type) {
                for (auto const& dic : __formatTypeDic__) {
                    if (dic.type == type)
                        return dic.name;
                }

                return "unknown";
            }

            formatType toFormatType(const char *name) {
                if (nullptr == name || 0 == strlen(name))
                    throw std::invalid_argument("invalid format type");

                std::string lname(name);
                std::transform(lname.begin(), lname.end(), lname.begin(), ::tolower);

                for (auto const& dic : __formatTypeDic__) {
                    if (lname == dic.name)
                        return dic.type;
                }

                for (auto const& dic : __formatTypeDic__) {
                    if (lname == dic.initial)
                        return dic.type;
                }

                return __formatTypeDic__[0].type;
            }

        }
    }
}
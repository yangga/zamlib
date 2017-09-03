//
// Created by SungWoo Yang on 2017. 9. 1..
//

#include "base.h"
#include "loggerDefine.h"

#include<boost/tokenizer.hpp>

#include <sstream>

namespace zam {
    namespace base {
        namespace log {

            /// level
            struct {
                level lv;
                const char* name;
                const char* initial;
            } __logLevelDic__ [] = {
                    {level::all,   "all",   "a"},
                    {level::trace, "trace", "t"},
                    {level::debug, "debug", "d"},
                    {level::info,  "info",  "i"},
                    {level::warn,  "warn",  "w"},
                    {level::error, "error", "e"},
                    {level::fatal, "fatal", "f"}
            };
            static_assert(0 < sizeof(__logLevelDic__));

            std::string toString(level lv) {
                for (auto const& dic : __logLevelDic__) {
                    if (dic.lv == lv)
                        return dic.name;
                }

                return __logLevelDic__[0].name;
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

            /// stream
            struct {
                streamType type;
                const char* name;
                const char* initial;
            } __streamTypeDic__ [] = {
                    {streamType::none,    "none",    "n"},
                    {streamType::console, "console", "c"},
                    {streamType::file,    "file",    "f"},
                    {streamType::tracer,  "tracer",  "t"},
                    {streamType::udp,     "udp",     "u"}
            };
            static_assert(0 < sizeof(__streamTypeDic__));

            std::string toString(streamType type) {
                for (auto const& dic : __streamTypeDic__) {
                    if (dic.type == type)
                        return dic.name;
                }

                return __streamTypeDic__[0].name;
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

        }
    }
}
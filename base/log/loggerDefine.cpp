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

            struct {
                level lv;
                const char* name;
            } __logLevelDic__ [] = {
                    {level::trace, "trace"},
                    {level::debug, "debug"},
                    {level::info, "info"},
                    {level::warn, "warn"},
                    {level::error, "error"},
                    {level::fatal, "fatal"},
            };
            std::string toString(level lv) {
                std::stringstream ss;

                for (auto const& dic : __logLevelDic__) {
                    if (0 < (dic.lv & lv)) {
                        if (0 < ss.tellp())
                            ss << "|";

                        ss << dic.name;
                    }
                }

                return ss.str();
            }

            level toLevel(const char* names) {
                assert(nullptr != names);

                if (nullptr == names || 0 == strlen(names))
                    throw std::invalid_argument("invalid names");

                std::string s(names);

                boost::char_separator<char> sep("|");
                boost::tokenizer<boost::char_separator<char> > tok(s, sep);

                uint32_t lv = 0;
                for (auto const& name : tok) {
                    for (auto const& dic : __logLevelDic__) {
                        if (name == dic.name)
                            lv |= dic.lv;
                    }
                }

                assert(0 != lv);
                return level(lv);
            }

        }
    }
}
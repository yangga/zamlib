//
// Created by SungWoo Yang on 2017. 8. 31..
//

#ifndef ZAM_LOGWRITERFACTORY_H
#define ZAM_LOGWRITERFACTORY_H

namespace zam {
    namespace base {
        namespace log {

            class loggerConfig;
            class loggerWriter;

            class logWriterFactory {
            public:
                static loggerWriter* createWithConfig(loggerConfig const& cfg);
                static loggerWriter* createWithJson(loggerConfig const& cfg);
            };

        }
    }
}


#endif //ZAM_LOGWRITERFACTORY_H

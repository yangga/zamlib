//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <ZamConfig.h>
#include <zam/base/logger.h>
#include <zam/base/filesystem/whereami.h>

#include <iostream>

int main(int argc, char* argv[]) {

    try {
        using namespace zam::base::log;

        std::string cfgPath(Zam_CMAKE_BUILT_PATH);
        cfgPath += "/misc/tests/test_logging/test_logging.json";

        loggerSystem::load(cfgPath.c_str());
    } catch(std::exception& e) {
        std::cerr << "failed to load - " << e.what() << std::endl;
        return -1;
    }
//
//    try {
//        for (int i=0; i<10; ++i) {
//            ZAM_LOGT("test1") << "trace";
//            ZAM_LOGD("test1") << "debug";
//            ZAM_LOGI("test1") << "info";
//            ZAM_LOGW("test1") << "warning";
//            ZAM_LOGE("test1") << "error";
//            ZAM_LOGF("test1") << "fatal";
//        }
//    } catch(std::exception& e) {
//        std::cerr << "failed to log - " << e.what() << std::endl;
//    }


    return 0;
}

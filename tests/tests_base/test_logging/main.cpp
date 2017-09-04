//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <base/logger.h>
#include <base/filesystem/whereami.h>

#include <iostream>

int main(int argc, char* argv[]) {

    try {
        std::cout << "zam::base::filesystem::whereami::module_dir() - " << zam::base::filesystem::whereami::module_dir() << std::endl;
        chdir(zam::base::filesystem::whereami::module_dir().c_str());

        using namespace zam::base::log;

        loggerSystem::load("../misc/tests/test_logging/test_logging.json");
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    ZAM_LOGT("test1") << "trace";
    ZAM_LOGD("test1") << "debug";
    ZAM_LOGI("test1") << "info";
    ZAM_LOGW("test1") << "warning";
    ZAM_LOGE("test1") << "error";
    ZAM_LOGF("test1") << "fatal";

    return 0;
}

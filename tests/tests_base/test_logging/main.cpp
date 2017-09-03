//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <base/logger.h>

#include <iostream>

using namespace zam::base::log;

int main(int argc, char* argv[]) {

    try {
        loggerSystem::load("../misc/tests/test_logging/test_logging.json");
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    ZAM_LOGD("test1") << "hello" << " world";
    ZAM_LOGW("test1") << "i wanna be a rich !!!" << " give me " << 1 << " dollar";

    return 0;
}

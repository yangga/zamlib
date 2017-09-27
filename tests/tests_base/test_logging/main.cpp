//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <ZamConfig.h>
#include <zam/base/logger.h>

int main(int argc, char* argv[]) {
    try {
        using namespace zam::base::log;

        std::string cfgPath(ZAM_CMAKE_BUILT_PATH);
        cfgPath += "/misc/tests/test_logging/test_logging.json";

        loggerSystem::load(cfgPath.c_str());
    } catch(std::exception& e) {
        std::cerr << "failed to load - " << e.what() << std::endl;
        return -1;
    }

    ZAM_LOGT("test1") << "trace";
    ZAM_LOGD("test1") << "debug";
    ZAM_LOGI("test1") << "info";
    ZAM_LOGW("test1") << "warning";
    ZAM_LOGE("test1") << "error";
    ZAM_LOGF("test1") << "fatal";

    struct TestBuf {
        int a = 1 << 1;
        int b = 1 << 2;
        int c = 1 << 3;
        int d = 1 << 4;
        char txt[80] = "hello world~!!!!!!";
    };
    TestBuf buf;
    ZAM_LOGD("test1") << ZAM_DUMP_INLINE(&buf, sizeof(buf));
    ZAM_LOGD("test1") << ZAM_DUMP_INLINE(&buf, sizeof(buf), sizeof(buf)-10);
    ZAM_LOGD("test1") << ZAM_DUMP(&buf, sizeof(buf));
    ZAM_LOGD("test1") << ZAM_DUMP(&buf, sizeof(buf), sizeof(buf)-10);

    return 0;
}

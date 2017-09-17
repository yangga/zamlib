//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <ZamConfig.h>
#include <zam/base/logger.h>

#include <zam/base/log/server/loggerUdpServer.h>

void udpLogHandler(char* buf, size_t buf_len, const boost::asio::ip::udp::endpoint& epRecv);


zam::base::io::ioSystem ios;
zam::base::log::server::loggerUdpServer udpServer(ios, 5050, udpLogHandler);


int main(int argc, char* argv[]) {
    try {
        /// begin server
        udpServer.start_receive();

        using namespace zam::base::log;

        std::string cfgPath(Zam_CMAKE_BUILT_PATH);
        cfgPath += "/misc/tests/test_logging_udp/test_logging_udp.json";

        loggerSystem::load(cfgPath.c_str());
    } catch(std::exception& e) {
        std::cerr << "failed to load - " << e.what() << std::endl;
        return -1;
    }

    auto sample_logging = [](){
        ZAM_LOGT("test1") << "trace";
        ZAM_LOGD("test1") << "debug";
        ZAM_LOGI("test1") << "info";
        ZAM_LOGW("test1") << "warning";
        ZAM_LOGE("test1") << "error";
        ZAM_LOGF("test1") << "fatal";

        /// after logging, stop ios service
        ios.stop();
    };

    std::thread(sample_logging).detach();

    /// blocked till finish ios service
    ios.start();

    return 0;
}


void udpLogHandler(char* buf, size_t buf_len, const boost::asio::ip::udp::endpoint& epRecv) {
    std::cout << "udpLogHandler - " << buf << " / from:" << epRecv.address().to_string() << std::endl;
}

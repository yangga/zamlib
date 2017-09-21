//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <ZamConfig.h>
#include <zam/base/logger.h>

#include <zam/base/log/server/loggerUdpServer.h>

void udpLogHandler(char* buf, size_t buf_len, const boost::asio::ip::udp::endpoint& epRecv);


boost::shared_ptr<zam::base::io::ioSystem> ios;
boost::shared_ptr<zam::base::log::server::loggerUdpServer> udpServer;


int main(int argc, char* argv[]) {
    try {
		ios = boost::make_shared<zam::base::io::ioSystem>();
		udpServer = boost::make_shared<zam::base::log::server::loggerUdpServer>(*ios, 7070, udpLogHandler);

        /// begin server
        udpServer->start_receive();

        using namespace zam::base::log;

        std::string cfgPath(ZAM_CMAKE_BUILT_PATH);
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
        ios->stop();
    };

    std::thread(sample_logging).detach();

    /// blocked till finish ios service
    ios->start();

    return 0;
}


void udpLogHandler(char* buf, size_t buf_len, const boost::asio::ip::udp::endpoint& epRecv) {
    std::cout << "udpLogHandler - " << buf << " / from:" << epRecv.address().to_string() << std::endl;
}

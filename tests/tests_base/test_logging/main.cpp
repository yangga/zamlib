//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <ZamConfig.h>
#include <zam/base/logger.h>
#include <zam/base/filesystem/whereami.h>

#include <zam/base/log/server/loggerUdpServer.h>

#include <boost/asio.hpp>

#include <thread>

void udpLogHandler(char* buf, size_t buf_len, const boost::asio::ip::udp::endpoint& epRecv);

boost::asio::io_service ios;
zam::base::log::server::loggerUdpServer udpServer(ios, 5050, udpLogHandler);


void start_udp_log_server() {
    udpServer.start_receive();

    auto io_thread = [&](){
        while (!ios.stopped()){
            try {
                ios.run();
            }
            catch (const std::exception& e) {
                ZAM_LOGE("root") << "io_service exception: " << e.what();
            }
            catch (...) {
                ZAM_LOGE("root") << "io_service exception: unknown";
            }
        }
        ZAM_LOGI("root") << "io_service thread stopped";
    };

    std::thread t(io_thread);
    t.detach();
}

int main(int argc, char* argv[]) {
    try {
        start_udp_log_server();

        using namespace zam::base::log;

        std::string cfgPath(Zam_CMAKE_BUILT_PATH);
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

    /// waiting for udp logging finish
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    ios.stop();

    return 0;
}

void udpLogHandler(char* buf, size_t buf_len, const boost::asio::ip::udp::endpoint& epRecv) {
    std::cout << "udpLogHandler - " << buf << std::endl;
}

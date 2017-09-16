//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <ZamConfig.h>
#include <zam/base/logger.h>

#include <zam/base/log/server/loggerUdpServer.h>

#include <boost/asio.hpp>

#include <thread>

void start_udp_log_server();
void wait_udp_log_server_end();
void udpLogHandler(char* buf, size_t buf_len, const boost::asio::ip::udp::endpoint& epRecv);


zam::base::io::ioSystem ios;
zam::base::log::server::loggerUdpServer udpServer(ios, 5050, udpLogHandler);



int main(int argc, char* argv[]) {
    try {
        /// begin server
        start_udp_log_server();

        using namespace zam::base::log;

        std::string cfgPath(Zam_CMAKE_BUILT_PATH);
        cfgPath += "/misc/tests/test_logging_udp/test_logging_udp.json";

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

    wait_udp_log_server_end();

    return 0;
}

void start_udp_log_server() {
    udpServer.start_receive();

    auto io_thread_starter = [&]() {
        ios.start();
    };

    auto io_thread_stopper = [&](){
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
        ios.stop();
    };

    std::thread(io_thread_starter).detach();
    std::thread(io_thread_stopper).detach();
}

void wait_udp_log_server_end() {
    /// waitting for end server jobs
    while(!ios.stopped()){
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);
    }
}

void udpLogHandler(char* buf, size_t buf_len, const boost::asio::ip::udp::endpoint& epRecv) {
    std::cout << "udpLogHandler - " << buf << " / from:" << epRecv.address().to_string() << std::endl;
}

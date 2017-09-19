//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <ZamConfig.h>
#include <zam/base/logger.h>
#include <zam/base/io/ioSystem.h>

#include <zam/net/acceptor/acceptorTcp.h>

namespace base = zam::base;
namespace io = zam::base::io;
namespace net = zam::net;

zam::base::io::ioSystem ios;

void init_log_system();



int main(int argc, char* argv[]) {
    init_log_system();

    net::acceptorTcp::Config cfg {"0.0.0.0", 5050};
    net::acceptorTcp acceptor(ios, cfg);

    try {
        acceptor.startAccept();
    } catch(std::exception& e) {
        ZAM_LOGE("test1") << "err - " << e.what();
    }





//    net::acceptorCfg<
//            net::proto::tcp,
//            net::chiper::dev3,
//            net::handler
//            > cfg;
//
//    net::acceptor acceptor(ios);


//    zam::net::acceptor acceptor(ios);
//
//    protocol
//    cyper (en/decryptor)
//    parser
//    handler
//         single, multi
//    updateTime <= 이건 공용 service로 올리자

    auto do_shomething = [](){
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);

        ios.stop();
    };

    std::thread(do_shomething).detach();

    ios.start();

    return 0;
}




void init_log_system() {
    try {
        using namespace zam::base::log;

        std::string cfgPath(ZAM_CMAKE_BUILT_PATH);
        cfgPath += "/misc/tests/test_net_common/logger.json";

        loggerSystem::load(cfgPath.c_str());
    } catch(std::exception& e) {
        std::cerr << "failed to load - " << e.what() << std::endl;
        throw e;
    }
}


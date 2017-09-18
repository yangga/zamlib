//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <ZamConfig.h>
#include <zam/base/logger.h>
#include <zam/base/io/ioSystem.h>

zam::base::io::ioSystem ios;

void init_log_system();



int main(int argc, char* argv[]) {
    init_log_system();

    using namespace zam;

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


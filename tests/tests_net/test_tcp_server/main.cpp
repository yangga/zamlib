//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <ZamConfig.h>
#include <zam/base/logger.h>
#include <zam/base/io/ioSystem.h>

#include <zam/net/acceptor/acceptorTcp.h>
#include <zam/net/cipher/cipherNull.h>
#include <zam/net/handler/eventDispatcher.h>
#include <zam/net/packer/packerDefault.h>

#include "my_handler.h"

namespace base = zam::base;
namespace io = zam::base::io;
namespace handler = zam::net::handler;
namespace net = zam::net;
namespace warehouse = zam::net::warehouse;

boost::shared_ptr<zam::base::io::ioSystem> ios;

void init_log_system();



int main(int argc, char* argv[]) {
    init_log_system();

	ios = boost::make_shared<zam::base::io::ioSystem>();

    warehouse::warehouse wh;
    wh.getCipher = []() -> net::cipher_ptr_t {
        return boost::make_shared<net::cipher::cipherNull>();
    };
    wh.getEventHandler = []() -> net::eventHandler_ptr_t {
        static net::eventHandler_ptr_t s_event_handler(new handler::eventDispatcherSingleThread<my_handler>(*ios));
        return s_event_handler;
    };
    wh.getPacker = []() -> net::packer_ptr_t {
        return boost::make_shared<net::packer::packerDefault>();
    };

    net::acceptor::acceptorTcp::Config cfg {"0.0.0.0", 8080};
    net::acceptor::acceptorTcp acceptor(*ios, wh, cfg);

    try {
        acceptor.startAccept();
    } catch(std::exception& e) {
        ZAM_LOGE("test1") << "err - " << e.what();
    }

//    net::message msgRecved;
//    size_t transported = 80;
//    net::messageIStream istreamRecv(msgRecved, transported);
//
//    net::packer::packer* packer;
//
//    net::message msgUnpacked;
//    auto const msgUnpackedLen = packer->unpack(msgUnpacked, istreamRecv);
//    msgRecved.squash(istreamRecv.readSize(), transported-istreamRecv.readSize());


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
        std::this_thread::sleep_for(10s);

        ios->stop();
    };

    std::thread(do_shomething).detach();

    ios->start();

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


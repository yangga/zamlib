//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <ZamConfig.h>
#include <zam/base/logger.h>
#include <zam/base/io/ioSystem.h>

#include <zam/net/connector/connectorTcp.h>
#include <zam/net/handler/eventDispatcher.h>
#include <zam/net/packer/packerDefault.h>

#include <zam/net/message/messageOStream.h>

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
        return nullptr;
    };
    wh.getEventHandler = []() -> net::eventHandler_ptr_t {
        static net::eventHandler_ptr_t s_event_handler(new handler::eventDispatcherSingleThread<my_handler>(*ios));
        return s_event_handler;
    };
    wh.getPacker = []() -> net::packer_ptr_t {
        return boost::make_shared<net::packer::packerDefault>();
    };

    net::connector::connectorTcp::Config cfg {"127.0.0.1", 8080};
    net::connector::connectorTcp connector(*ios, wh, cfg);

    net::connection_ptr_t conn;
    try {
        conn = connector.connect();
        ZAM_LOGD("test1") << "connected";
    } catch(std::exception& e) {
        ZAM_LOGE("test1") << "err - " << e.what();
        return 0;
    }

    auto do_shomething = [&](){
        net::message msg;
        net::messageOStream os(msg);

        os << std::string("hello world~!");
        conn->send(os);
        ZAM_LOGD("test1") << "sent message";

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);

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

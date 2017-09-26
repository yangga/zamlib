//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <zam/base/io/ioObject.h>
#include <zam/base/schedule/scheduler.h>

boost::shared_ptr<zam::base::io::ioSystem> ios;

class GameObject : public zam::base::io::ioObject
{
public:
    explicit GameObject(zam::base::io::ioSystem& ios)
            : zam::base::io::ioObject(ios)
            , scheduler_(boost::make_shared<zam::base::schedule::scheduler>(*this))
    {}

    void startTimer() {
        // call GameObject::onAt() at specific time
        scheduler_->at("timer_at"
                , boost::bind<void>(&GameObject::onAt, this)
                , boost::asio::deadline_timer::traits_type::now() + boost::posix_time::milliseconds(500));

        // call GameObject::onLoop() 3 times each seconds
        scheduler_->loop("timer_loop", boost::bind<void>(&GameObject::onLoop, this), boost::posix_time::seconds(1), 3);

        // call GameObject::onEnd() after 5 seconds
        scheduler_->once("timer_end", boost::bind<void>(&GameObject::onEnd, this), boost::posix_time::seconds(5));
    }

    void onAt() {
        std::cout << __FUNCTION__ << std::endl;
    }

    void onLoop() {
        std::cout << __FUNCTION__ << std::endl;
    }

    void onEnd() {
        std::cout << __FUNCTION__ << std::endl;
        ios().stop();
    }

private:
    boost::shared_ptr<zam::base::schedule::scheduler> scheduler_;
};

int main(int argc, char* argv[]) {
    ios = boost::make_shared<zam::base::io::ioSystem>();
    GameObject obj(*ios);

    std::thread([&](){
        obj.startTimer();
    }).detach();

    /// blocked till finish ios service
    ios->start();

    return 0;
}

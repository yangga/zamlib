//
// Created by SungWoo Yang on 2017. 9. 26..
//

#ifndef ZAMLIB_TEST_WAITQ_H
#define ZAMLIB_TEST_WAITQ_H

#include <zam/base/container/waitq.h>

#include <string>
#include <thread>

using namespace zam::base::container;

waitq<std::string> q;

void push_thread() {
    using namespace std::chrono_literals;

    std::this_thread::sleep_for(1s);
    q.push("hello!?");

    std::this_thread::sleep_for(1s);
    q.push("how are you?");

    std::this_thread::sleep_for(1s);
    q.push("bye");
}

void test_waitq() {

    std::cout << "[test_qvector]" << std::endl;
    std::cout << "======================" << std::endl;

    std::thread(push_thread).detach();

    std::string txt;
    while(txt != "bye") {
        // wait to pushed data
        if (!q.pop(txt))
            break;

        std::cout << txt << std::endl;
    }
    std::cout << "======================" << std::endl;
}

#endif //ZAMLIB_TEST_WAITQ_H

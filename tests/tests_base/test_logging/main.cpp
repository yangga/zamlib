//
// Created by SungWoo Yang on 2017. 8. 31..
//

#include <iostream>

#include <base/base.h>
#include <base/log/logger.h>

using namespace zam::base::log;

int main(int argc, char* argv[]) {
    logd("test") << "hello" << " world";
    logd("test") << "i wanna be a rich !!!" << " give me " << 1 << " dollar";

    return 0;
}

//
// Created by SungWoo Yang on 2017. 9. 25..
//

#ifndef ZAMLIB_PROTOCOL_1_H
#define ZAMLIB_PROTOCOL_1_H

#include <zam/net/net.h>

enum protocol_c_to_s : zam::net::protocol_t {
    c_s_json = 1000,
    c_s_struct = 1001,
    c_s_protobuf = 1002
};

enum protocol_s_to_c : zam::net::protocol_t {
    s_c_json = 2000,
    s_c_struct = 2001,
    s_c_protobuf = 2002
};

struct sample_struct_data {
    int a = 0;
    float b = 0;
    double c = 0;
    char d[80] = {0,};
};

#endif //ZAMLIB_PROTOCOL_1_H

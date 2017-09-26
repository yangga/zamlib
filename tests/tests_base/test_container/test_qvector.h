//
// Created by SungWoo Yang on 2017. 9. 26..
//

#ifndef ZAMLIB_TEST_QVECTOR_H
#define ZAMLIB_TEST_QVECTOR_H

#include <zam/base/container/qvector.h>

#include <iostream>

using namespace zam::base::container;

void test_qvector_int() {
    std::cout << "======================" << std::endl;
    std::cout << __FUNCTION__ << std::endl;

    qvector<int> cont;
    cont.push(100);
    cont.push(99);
    cont.push(88);
    cont.push(123);
    cont.push(999);

    for (auto& e : cont) {
        std::cout << e << std::endl;
    }
}

struct CustomType {
    int n1;
    float n2;
};

bool operator == (const CustomType& lh, const CustomType& rh) {
    return (lh.n1 == rh.n1 && lh.n2 && rh.n2);
}

bool operator < (const CustomType& lh, const CustomType& rh) {
    return (lh.n1 != rh.n1) ? (lh.n1 < rh.n1) : (lh.n2 < rh.n2);
}


void test_qvector_custom_type() {
    std::cout << "======================" << std::endl;
    std::cout << __FUNCTION__ << std::endl;
    qvector<CustomType> cont;
    cont.push(CustomType{1000, 1.11f});
    cont.push(CustomType{20, 2.22f});
    cont.push(CustomType{-22, -2.22f});
    cont.push(CustomType{-22, -1.11f});
    cont.push(CustomType{20, -2.22f});

    for (auto& e : cont) {
        std::cout << e.n1 << ", " << e.n2 << std::endl;
    }
}

void test_qvector()
{
    test_qvector_int();
    test_qvector_custom_type();
}

#endif //ZAMLIB_TEST_QVECTOR_H

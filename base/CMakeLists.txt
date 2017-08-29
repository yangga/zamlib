cmake_minimum_required(VERSION 3.8)
project(base)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES library.cpp library.h)
add_library(base ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.8)
project(net)

set(CMAKE_CXX_STANDARD 17)

include_directories ("${PROJECT_SOURCE_DIR}")

set(SOURCE_FILES library.cpp library.h stdafx.h)
add_library(net ${SOURCE_FILES})
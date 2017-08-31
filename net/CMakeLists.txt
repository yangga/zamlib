cmake_minimum_required(VERSION 3.8)
project(net)

set(CMAKE_CXX_STANDARD 17)

find_package(boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories ("${PROJECT_SOURCE_DIR}")
include_directories ("${PROJECT_BINARY_DIR}")

set(SOURCE_FILES library.cpp library.h stdafx.h)
add_library(net ${SOURCE_FILES})
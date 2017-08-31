cmake_minimum_required(VERSION 3.8)
project(test_logging)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(test_logging ${SOURCE_FILES})

set(LIBRARY_FILES base)
target_link_libraries (test_logging ${LIBRARY_FILES})

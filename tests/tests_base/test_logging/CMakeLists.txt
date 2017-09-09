cmake_minimum_required(VERSION 3.8)
project(test_logging)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(test_logging ${SOURCE_FILES})

set(LIBRARY_FILES zam_base_static ${Boost_LIBRARIES} jsoncpp_lib_static pthread)
target_link_libraries (test_logging ${LIBRARY_FILES})

include(CTest)

# 1st test run
add_test (test_logging_runs_1 "${EXECUTABLE_OUTPUT_PATH}/test_logging" "")

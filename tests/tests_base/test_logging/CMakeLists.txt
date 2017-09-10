cmake_minimum_required(VERSION 3.8)
project(test_logging)

set(CMAKE_CXX_STANDARD 14)

include_directories(${ZAMLIB_ROOT} ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES main.cpp)
add_executable(test_logging ${SOURCE_FILES})

set(LIBRARY_FILES zam_base_shared ${Boost_LIBRARIES} ${JSONCPP_LIBRARY})

if(MSVC)
    set(LIBRARY_FILES ${LIBRARY_FILES} Ws2_32)
else(MSVC)
    set(LIBRARY_FILES ${LIBRARY_FILES} pthread)
endif(MSVC)

target_link_libraries (test_logging ${LIBRARY_FILES})

include(CTest)

# 1st test run
add_test (test_logging_runs_1 "${EXECUTABLE_OUTPUT_PATH}/test_logging" "")

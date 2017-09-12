cmake_minimum_required(VERSION 3.8)
project(test_logging)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR} ${ZAMLIB_ROOT} ${JSONCPP_INCLUDE_DIR_ROOT})

set(SOURCE_FILES main.cpp)
add_executable(test_logging ${SOURCE_FILES})

set(LIBRARY_FILES zam_base_shared ${Boost_LIBRARIES} ${JSONCPP_LIBRARY})

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")   # turn off deprecated warning (latest jsoncpp has lots of deprecated warning)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4819")   # trun off code page warning
    set(LIBRARY_FILES ${LIBRARY_FILES} Ws2_32)
else(MSVC)
    set(LIBRARY_FILES ${LIBRARY_FILES} pthread)
endif(MSVC)

target_link_libraries (test_logging ${LIBRARY_FILES})

include(CTest)

# 1st test run
add_test (test_logging_runs_1 "${EXECUTABLE_OUTPUT_PATH}/test_logging" "")

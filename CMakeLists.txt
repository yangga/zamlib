cmake_minimum_required(VERSION 3.8)
project(zam)

set(CMAKE_CXX_STANDARD 17)

# The version number.
set (Zam_VERSION_MAJOR 0)
set (Zam_VERSION_MINOR 1)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# setup directory where we should look for cmake files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# checking libraries
# boost
find_package(boost REQUIRED)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
else(Boost_FOUND)
	message(FATAL_ERROR "you need to boost library")
endif(Boost_FOUND)
# jsoncpp
find_package(Jsoncpp REQUIRED)
if(JSONCPP_FOUND)
	include_directories(${JSONCPP_INCLUDE_DIR})
else(JSONCPP_FOUND)
	message(FATAL_ERROR "you need to jsoncpp library")
endif(JSONCPP_FOUND)


# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/ZamConfig.h.in"
	"${PROJECT_BINARY_DIR}/ZamConfig.h"
	)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories ("${PROJECT_BINARY_DIR}")

add_subdirectory(base)
add_subdirectory(net)

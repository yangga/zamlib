cmake_minimum_required(VERSION 3.8)
project(zam)

set(CMAKE_CXX_STANDARD 17)

# The version number.
set (Zam_VERSION_MAJOR 0)
set (Zam_VERSION_MINOR 1)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/ZamConfig.h.in"
	"${PROJECT_BINARY_DIR}/ZamConfig.h"
	)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(base)
add_subdirectory(net)

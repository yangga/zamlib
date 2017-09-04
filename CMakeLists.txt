cmake_minimum_required(VERSION 3.8)
project(zamlib)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD 17)

# The version number.
set (Zam_VERSION_MAJOR 0)
set (Zam_VERSION_MINOR 1)

set(ROOT_INSTALL_PATH ${PROJECT_NAME})

# Enable testing function
enable_testing()

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
		"${PROJECT_SOURCE_DIR}/ZamConfig.h.in"
		"${PROJECT_BINARY_DIR}/ZamConfig.h"
)

# output path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# setup directory where we should look for cmake files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# checking libraries
# Boost
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost REQUIRED COMPONENTS date_time filesystem iostreams system serialization log log_setup thread)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	#link_directories(${Boost_LIBRARY_DIRS})
else(Boost_FOUND)
	if(MSVC)
		message("You need to add entries - BOOST_INCLUDEDIR, BOOST_LIBRARYDIR, BOOST_ROOT")
	else(MSVC)
		message(FATAL_ERROR "you need to boost library")
	endif(MSVC)
endif(Boost_FOUND)
# Jsoncpp
find_package(Jsoncpp REQUIRED)
if(JSONCPP_FOUND)
	include_directories(${JSONCPP_INCLUDE_DIR})
else(JSONCPP_FOUND)
	if(MSVC)
		message("You need to add entries - JSONCPP_INCLUDE_DIR, JSONCPP_LIBRARY")
	else(MSVC)
		message(FATAL_ERROR "you need to jsoncpp library")
	endif(MSVC)
endif(JSONCPP_FOUND)


include_directories ("${PROJECT_SOURCE_DIR}")
include_directories ("${LIBRARY_OUTPUT_PATH}")

install (FILES "${PROJECT_BINARY_DIR}/ZamConfig.h"
		DESTINATION ${ROOT_INSTALL_PATH})

# setup directory where we should look for cmake files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# checking libraries
# Boost
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost REQUIRED COMPONENTS date_time filesystem iostreams system serialization log log_setup thread)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	#link_directories(${Boost_LIBRARY_DIRS})
else(Boost_FOUND)
	message(FATAL_ERROR "you need to boost library")
endif(Boost_FOUND)
# Jsoncpp
find_package(Jsoncpp REQUIRED)
if(JSONCPP_FOUND)
	include_directories(${JSONCPP_INCLUDE_DIR})
else(JSONCPP_FOUND)
	message(FATAL_ERROR "you need to jsoncpp library")
endif(JSONCPP_FOUND)


include_directories ("${PROJECT_SOURCE_DIR}")
include_directories ("${PROJECT_BINARY_DIR}")

add_subdirectory(base)
add_subdirectory(net)
add_subdirectory(tests)

# CPack
include(CPack)


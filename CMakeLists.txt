cmake_minimum_required(VERSION 3.2.2)
project(zamlib)

set(CMAKE_CXX_STANDARD 14)

# The version number.
set (Zam_VERSION_MAJOR 0)
set (Zam_VERSION_MINOR 1)
set (Zam_VERSION_PATCH 0)

set(ROOT_INSTALL_PATH ${PROJECT_NAME})

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
		"${PROJECT_SOURCE_DIR}/ZamConfig.h.in"
		"${PROJECT_BINARY_DIR}/ZamConfig.h"
)

# output path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# setup directory where we should look for cmake files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# checking libraries
# Boost
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.55 REQUIRED COMPONENTS date_time filesystem iostreams system serialization log log_setup thread)
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

######################################################################
# Enable testing function
enable_testing()

######################################################################
# sub projects
add_subdirectory(base)
add_subdirectory(net)
add_subdirectory(tests)

######################################################################
# CPack

# reset global path
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++ library for game server")
set(CPACK_PACKAGE_VENDOR "teamzam")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_CONTACT "https://github.com/yangga/zamlib")
set(CPACK_PACKAGE_VERSION_MAJOR "${Zam_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Zam_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${Zam_VERSION_PATCH}")
set(PACKAGE_VERSION "${Zam_VERSION_MAJOR}.${Zam_VERSION_MINOR}.${Zam_VERSION_PATCH}")
set(TARGET_ARCH ${CMAKE_SYSTEM_NAME})

if(APPLE)
    set(CPACK_GENERATOR DragNDrop)
    set(CMAKE_INSTALL_PREFIX /usr/local)
    set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
    set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PACKAGE_VERSION}-osx-${TARGET_ARCH}")
    set(CPACK_SOURCE_PACKAGE_FILE_NAME  "${PROJECT_NAME}-${PACKAGE_VERSION}-osx-src")
    set(CPACK_BUNDLE_NAME ${PROJECT_NAME})
elseif(UNIX)
    set(CPACK_GENERATOR "${SPECIFIC_SYSTEM_PREFERED_CPACK_GENERATOR}") # Distribution packaging formats ("make package") might be overrided later
    set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PACKAGE_VERSION}-linux-${TARGET_ARCH}")
    set(CPACK_SOURCE_PACKAGE_FILE_NAME  "${PROJECT_NAME}-${PACKAGE_VERSION}-linux-src")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}-${PACKAGE_VERSION}")
elseif(MINGW)
    set(CPACK_SET_DESTDIR FALSE)
    set(CPACK_GENERATOR "NSIS") # Distribution packaging formats ("make package")
    set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PACKAGE_VERSION}-${MINGW_PACK_NAME}")
    set(CPACK_NSIS_PACKAGE_NAME "${PROJECT_NAME}-${PACKAGE_VERSION}")
    set(CPACK_NSIS_DISPLAY_NAME "zamlib_${Zam_VERSION_MAJOR}_${Zam_VERSION_MINOR}_${Zam_VERSION_PATCH}")
    set(CPACK_NSIS_MODIFY_PATH "ON")
    set(CPACK_NSIS_HELP_LINK "https://github.com/yangga/zamlib")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/yangga/zamlib")
    set(CPACK_NSIS_CONTACT "${CPACK_PACKAGE_CONTACT}")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}-${PACKAGE_VERSION}")
elseif(MSVC)
    set(CPACK_SET_DESTDIR FALSE)
    set(CPACK_GENERATOR "NSIS") # Distribution packaging formats ("make package")
    set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PACKAGE_VERSION}")
    set(CPACK_NSIS_PACKAGE_NAME "${PROJECT_NAME}-${PACKAGE_VERSION}")
    set(CPACK_NSIS_DISPLAY_NAME "zamlib_${Zam_VERSION_MAJOR}_${Zam_VERSION_MINOR}_${Zam_VERSION_PATCH}")
    set(CPACK_NSIS_MODIFY_PATH "ON")
    set(CPACK_NSIS_HELP_LINK "https://github.com/yangga/zamlib")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/yangga/zamlib")
    set(CPACK_NSIS_CONTACT "${CPACK_PACKAGE_CONTACT}")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}-${PACKAGE_VERSION}")
endif()


include(CPack)

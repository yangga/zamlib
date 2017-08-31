cmake_minimum_required(VERSION 3.8)
project(base)

set(CMAKE_CXX_STANDARD 17)



include_directories ("${PROJECT_SOURCE_DIR}")

set(SOURCE_FILES library.cpp library.h log/logger.cpp log/logger.h log/loggerConfig.cpp log/loggerConfig.h log/loggerDefine.h stdafx.h log/detail/logWriter.cpp log/detail/logWriter.h log/detail/logWriterFactory.cpp log/detail/logWriterFactory.h)
add_library(base ${SOURCE_FILES})
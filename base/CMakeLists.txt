cmake_minimum_required(VERSION 3.8)
project(base)

set(CMAKE_CXX_STANDARD 17)

include_directories ("${PROJECT_SOURCE_DIR}")

set(SOURCE_FILES library.cpp library.h log/logger.cpp log/logger.h log/loggerConfig.cpp log/loggerConfig.h log/loggerDefine.h base.h log/detail/logWriter.cpp log/detail/logWriter.h log/detail/logWriterFactory.cpp log/detail/logWriterFactory.h ../tests/tests_base/test_logging/main.cpp log/loggerSystem.cpp log/loggerSystem.h log/detail/loggerInitializer.cpp log/detail/loggerInitializer.h logger.h log/stream/loggerStreamConsole.cpp log/stream/loggerStreamConsole.h log/stream/loggerStream.h log/loggerDefine.cpp log/allocator/loggerAllocConsole.cpp log/allocator/loggerAllocConsole.h log/allocator/loggerAlloc.h log/allocator/loggerAllocFile.cpp log/allocator/loggerAllocFile.h)
add_library(base ${SOURCE_FILES})
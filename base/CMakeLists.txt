cmake_minimum_required(VERSION 3.2.2)
project(base)

set(CMAKE_CXX_STANDARD 14)

set(LOCAL_INSTALL_PATH "${ROOT_INSTALL_PATH}/${PROJECT_NAME}")

include_directories (${PROJECT_SOURCE_DIR})

set(SOURCE_FILES log/logger.cpp log/logger.h log/loggerDefine.h base.h log/detail/loggerWriter.cpp log/detail/loggerWriter.h ../tests/tests_base/test_logging/main.cpp log/loggerSystem.cpp log/loggerSystem.h log/detail/loggerInitializer.cpp log/detail/loggerInitializer.h logger.h log/loggerDefine.cpp log/appender/loggerAppenderConsole.cpp log/appender/loggerAppenderConsole.h log/appender/loggerAppender.h log/appender/loggerAppenderFile.cpp log/appender/loggerAppenderFile.h log/appender/loggerAppenderTracer.cpp log/appender/loggerAppenderTracer.h log/appender/loggerAppenderUdp.cpp log/appender/loggerAppenderUdp.h log/detail/loggerPool.cpp log/detail/loggerPool.h log/detail/loggerSystemInitOnce.cpp log/detail/loggerSystemInitOnce.h 3rdParty/whereami-cpp/whereami++.cpp 3rdParty/whereami-cpp/whereami++.hpp 3rdParty/whereami-cpp/whereami.c 3rdParty/whereami-cpp/whereami.h filesystem/whereami.h log/detail/loggerAttrName.h log/detail/loggerAttrName.cpp log/appender/collector/collectorDefault.cpp log/appender/collector/collectorDefault.h)

add_library(base ${SOURCE_FILES})

set(DEPENDENT_LIBRARY_FILES jsoncpp_lib_static)
target_link_libraries (base ${DEPENDENT_LIBRARY_FILES})

# add the install targets
install (TARGETS base DESTINATION zamlib/lib)

file(GLOB DEPLOY_FILES_AND_DIRS "${PROJECT_SOURCE_DIR}/*")
foreach(ITEM ${DEPLOY_FILES_AND_DIRS})
    IF( IS_DIRECTORY "${ITEM}" )
        LIST( APPEND DIRS_TO_DEPLOY "${ITEM}" )
    ELSE()
        LIST( APPEND FILES_TO_DEPLOY "${ITEM}" )
    ENDIF()
endforeach()
install( FILES ${FILES_TO_DEPLOY} DESTINATION ${LOCAL_INSTALL_PATH} )
install( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION ${LOCAL_INSTALL_PATH} )

cmake_minimum_required(VERSION 3.8)
project(base)

set(CMAKE_CXX_STANDARD 14)

set(LOCAL_INSTALL_PATH "${ROOT_INSTALL_PATH}/${PROJECT_NAME}")

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${JSONCPP_INCLUDE_DIR_ROOT})

set(SOURCE_FILES log/logger.cpp log/logger.h log/loggerDefine.h base.h log/detail/loggerWriter.cpp log/detail/loggerWriter.h log/loggerSystem.cpp log/loggerSystem.h log/detail/loggerInitializer.cpp log/detail/loggerInitializer.h logger.h log/loggerDefine.cpp log/appender/loggerAppenderConsole.cpp log/appender/loggerAppenderConsole.h log/appender/loggerAppender.h log/appender/loggerAppenderFile.cpp log/appender/loggerAppenderFile.h log/appender/loggerAppenderTracer.cpp log/appender/loggerAppenderTracer.h log/appender/loggerAppenderUdp.cpp log/appender/loggerAppenderUdp.h log/detail/loggerPool.cpp log/detail/loggerPool.h log/detail/loggerSystemInitOnce.cpp log/detail/loggerSystemInitOnce.h 3rdParty/whereami-cpp/whereami++.cpp 3rdParty/whereami-cpp/whereami++.hpp 3rdParty/whereami-cpp/whereami.c 3rdParty/whereami-cpp/whereami.h filesystem/whereami.h log/detail/loggerAttrName.h log/detail/loggerAttrName.cpp log/appender/collector/collectorDefault.cpp log/appender/collector/collectorDefault.h)

# this is the "object library" target: compiles the sources only once
add_library(zambase OBJECT ${SOURCE_FILES})
# shared libraries need PIC
set_property(TARGET ${zambase} PROPERTY POSITION_INDEPENDENT_CODE ON)

# shared and static libraries built from the same object files
add_library(zam_base_shared SHARED $<TARGET_OBJECTS:zambase>)
add_library(zam_base_static STATIC $<TARGET_OBJECTS:zambase>)

# set OUTPUT NAME
set_target_properties(zam_base_shared PROPERTIES OUTPUT_NAME base)
set_target_properties(zam_base_static PROPERTIES OUTPUT_NAME base)

# dylib needs static libraries linkning
set(DEPENDENT_LIBRARY_FILES jsoncpp_lib_static ${Boost_LIBRARIES})
target_link_libraries (zam_base_shared ${DEPENDENT_LIBRARY_FILES})

# add the install targets
install (TARGETS zam_base_shared DESTINATION zamlib/lib)
install (TARGETS zam_base_static DESTINATION zamlib/lib)

install(DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION ${LOCAL_INSTALL_PATH}
        FILES_MATCHING PATTERN "*.h")

#file(GLOB DEPLOY_FILES_AND_DIRS "${PROJECT_SOURCE_DIR}/*")
#foreach(ITEM ${DEPLOY_FILES_AND_DIRS})
#    IF( IS_DIRECTORY "${ITEM}" )
#        LIST( APPEND DIRS_TO_DEPLOY "${ITEM}" )
#    ELSE()
#        LIST( APPEND FILES_TO_DEPLOY "${ITEM}" )
#    ENDIF()
#endforeach()
#install( FILES ${FILES_TO_DEPLOY} DESTINATION ${LOCAL_INSTALL_PATH} )
#install( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION ${LOCAL_INSTALL_PATH} )

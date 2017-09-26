cmake_minimum_required(VERSION 3.2.2)
project(base)

set(CMAKE_CXX_STANDARD 14)

include_directories(../.. ${JSONCPP_INCLUDE_DIR_ROOT})

set(SOURCE_FILES log/logger.h log/loggerDefine.h base.h log/detail/loggerWriter.h log/loggerSystem.cpp log/loggerSystem.h log/detail/loggerInitializer.cpp log/detail/loggerInitializer.h logger.h log/loggerDefine.cpp log/appender/loggerAppenderConsole.cpp log/appender/loggerAppenderConsole.h log/appender/loggerAppender.h log/appender/loggerAppenderFile.cpp log/appender/loggerAppenderFile.h log/appender/loggerAppenderTracer.cpp log/appender/loggerAppenderTracer.h log/appender/loggerAppenderUdp.cpp log/appender/loggerAppenderUdp.h log/detail/loggerPool.cpp log/detail/loggerPool.h log/detail/loggerSystemInitOnce.cpp log/detail/loggerSystemInitOnce.h 3rdParty/whereami-cpp/whereami++.cpp 3rdParty/whereami-cpp/whereami++.hpp 3rdParty/whereami-cpp/whereami.c 3rdParty/whereami-cpp/whereami.h filesystem/whereami.h log/detail/loggerAttrName.h log/detail/loggerAttrName.cpp log/appender/collector/collectorDefault.cpp log/appender/collector/collectorDefault.h log/appender/detail/frontendCreator.h log/appender/detail/frontendFormatFactory.cpp log/appender/detail/frontendFormatFactory.h log/appender/loggerAppenderSyslog.cpp log/appender/loggerAppenderSyslog.h log/server/loggerUdpServer.cpp log/server/loggerUdpServer.h log/appender/appenderPool.cpp log/appender/appenderPool.h io/ioSystem.cpp io/ioSystem.h buffer.h stream/streamInputBuf.h stream/streamOutputBuf.h memory/pool.h thread/staticValue.h exception.h io/ioObject.h log/logger.cpp log/detail/loggerWriter.cpp schedule/scheduler.cpp schedule/scheduler.h macro.h thread/lockObject.h io/ioObject.cpp)

###########################################################
# setting libraries

# shared
add_library(zam_base_shared SHARED ${SOURCE_FILES})
set_target_properties(zam_base_shared PROPERTIES OUTPUT_NAME base)

# dylib needs static libraries linkning
if(APPLE OR MSVC)
    set(DEPENDENT_LIBRARY_FILES ${JSONCPP_LIBRARY} ${Boost_LIBRARIES})

    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")   # turn off deprecated warning (latest jsoncpp has lots of deprecated warning)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4819")   # trun off code page warning
        set(DEPENDENT_LIBRARY_FILES ${DEPENDENT_LIBRARY_FILES} Ws2_32)
    else(MSVC)
        set(DEPENDENT_LIBRARY_FILES ${DEPENDENT_LIBRARY_FILES} pthread)
    endif(MSVC)

    target_link_libraries (zam_base_shared ${DEPENDENT_LIBRARY_FILES})
endif()

# static
add_library(zam_base_static STATIC ${SOURCE_FILES})
set_target_properties(zam_base_static PROPERTIES OUTPUT_NAME base_static)

# additional static options
StaticCompile(zam_base_static)

###########################################################
# installing libraries

# lib files
install(TARGETS zam_base_shared DESTINATION ${ROOT_INSTALL_PATH}/lib)
install(TARGETS zam_base_static DESTINATION ${ROOT_INSTALL_PATH}/lib)


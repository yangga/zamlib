cmake_minimum_required(VERSION 3.8)
project(base)

set(CMAKE_CXX_STANDARD 14)

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${JSONCPP_INCLUDE_DIR_ROOT})

set(SOURCE_FILES log/logger.cpp log/logger.h log/loggerDefine.h base.h log/detail/loggerWriter.cpp log/detail/loggerWriter.h log/loggerSystem.cpp log/loggerSystem.h log/detail/loggerInitializer.cpp log/detail/loggerInitializer.h logger.h log/loggerDefine.cpp log/appender/loggerAppenderConsole.cpp log/appender/loggerAppenderConsole.h log/appender/loggerAppender.h log/appender/loggerAppenderFile.cpp log/appender/loggerAppenderFile.h log/appender/loggerAppenderTracer.cpp log/appender/loggerAppenderTracer.h log/appender/loggerAppenderUdp.cpp log/appender/loggerAppenderUdp.h log/detail/loggerPool.cpp log/detail/loggerPool.h log/detail/loggerSystemInitOnce.cpp log/detail/loggerSystemInitOnce.h 3rdParty/whereami-cpp/whereami++.cpp 3rdParty/whereami-cpp/whereami++.hpp 3rdParty/whereami-cpp/whereami.c 3rdParty/whereami-cpp/whereami.h filesystem/whereami.h log/detail/loggerAttrName.h log/detail/loggerAttrName.cpp log/appender/collector/collectorDefault.cpp log/appender/collector/collectorDefault.h)


###########################################################
# static
EnableMTFlag()
add_library(zam_base_static STATIC ${SOURCE_FILES})

# set OUTPUT NAME
set_target_properties(zam_base_static PROPERTIES OUTPUT_NAME base_static)

###########################################################
# shared
EnableMDFlag()
add_library(zam_base_shared SHARED ${SOURCE_FILES})

# set OUTPUT NAME
set_target_properties(zam_base_shared PROPERTIES OUTPUT_NAME base)

# dylib needs static libraries linkning
if(APPLE OR MSVC)
    set(DEPENDENT_LIBRARY_FILES ${JSONCPP_LIBRARY} ${Boost_LIBRARIES})
    target_link_libraries (zam_base_shared ${DEPENDENT_LIBRARY_FILES})
endif()

###########################################################
# add the install targets
install (TARGETS zam_base_shared DESTINATION ${ROOT_INSTALL_PATH}/lib)
install (TARGETS zam_base_static DESTINATION ${ROOT_INSTALL_PATH}/lib)

install(DIRECTORY ${PROJECT_SOURCE_DIR} DESTINATION ${ROOT_INSTALL_PATH}
        FILES_MATCHING PATTERN "*.h"
        PATTERN "CMakeFiles" EXCLUDE
        )

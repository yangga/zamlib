cmake_minimum_required(VERSION 3.8)


set(CMAKE_CXX_STANDARD 14)

set(INCLUDE_DIRECTORIES ${JSONCPP_INCLUDE_DIR_ROOT})
set(SOURCE_FILES log/logger.cpp log/logger.h log/loggerDefine.h base.h log/detail/loggerWriter.cpp log/detail/loggerWriter.h log/loggerSystem.cpp log/loggerSystem.h log/detail/loggerInitializer.cpp log/detail/loggerInitializer.h logger.h log/loggerDefine.cpp log/appender/loggerAppenderConsole.cpp log/appender/loggerAppenderConsole.h log/appender/loggerAppender.h log/appender/loggerAppenderFile.cpp log/appender/loggerAppenderFile.h log/appender/loggerAppenderTracer.cpp log/appender/loggerAppenderTracer.h log/appender/loggerAppenderUdp.cpp log/appender/loggerAppenderUdp.h log/detail/loggerPool.cpp log/detail/loggerPool.h log/detail/loggerSystemInitOnce.cpp log/detail/loggerSystemInitOnce.h 3rdParty/whereami-cpp/whereami++.cpp 3rdParty/whereami-cpp/whereami++.hpp 3rdParty/whereami-cpp/whereami.c 3rdParty/whereami-cpp/whereami.h filesystem/whereami.h log/detail/loggerAttrName.h log/detail/loggerAttrName.cpp log/appender/collector/collectorDefault.cpp log/appender/collector/collectorDefault.h)


###########################################################
# static
foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if(${flag_var} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        message("${flag_var} - ${${flag_var}}")
    endif(${flag_var} MATCHES "/MD")
endforeach(flag_var)
project(baseStatic)
include_directories(${PROJECT_SOURCE_DIR} ${INCLUDE_DIRECTORIES})
add_library(zam_base_static STATIC ${SOURCE_FILES})

# set OUTPUT NAME
set_target_properties(zam_base_static PROPERTIES OUTPUT_NAME base_static)

# install lib
install (TARGETS zam_base_static DESTINATION ${ROOT_INSTALL_PATH}/lib)

###########################################################
# shared
#foreach(flag_var
#        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
#        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
#    if(${flag_var} MATCHES "/MT")
#        string(REGEX REPLACE "/MT" "/MD" ${flag_var} "${${flag_var}}")
#        message("${flag_var} - ${${flag_var}}")
#    endif(${flag_var} MATCHES "/MT")
#endforeach(flag_var)
project(base)
include_directories(${PROJECT_SOURCE_DIR} ${INCLUDE_DIRECTORIES})
add_library(zam_base_shared SHARED ${SOURCE_FILES})

# set OUTPUT NAME
set_target_properties(zam_base_shared PROPERTIES OUTPUT_NAME base)

# dylib needs static libraries linkning
if(APPLE OR MSVC)
    set(DEPENDENT_LIBRARY_FILES ${JSONCPP_LIBRARY} ${Boost_LIBRARIES})
    target_link_libraries (zam_base_shared ${DEPENDENT_LIBRARY_FILES})
endif()

# install lib
install (TARGETS zam_base_shared DESTINATION ${ROOT_INSTALL_PATH}/lib)

###########################################################
# install headers
project(baseHeader)

install(DIRECTORY ${PROJECT_SOURCE_DIR} DESTINATION ${ROOT_INSTALL_PATH}
        FILES_MATCHING PATTERN "*.h"
        PATTERN "CMakeFiles" EXCLUDE
        )

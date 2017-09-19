cmake_minimum_required(VERSION 3.8)
project(net)

set(CMAKE_CXX_STANDARD 14)

include_directories(../.. ${JSONCPP_INCLUDE_DIR_ROOT})

set(SOURCE_FILES acceptor/acceptor.h message/message.cpp message/message.h message/messageIStream.cpp message/messageIStream.h message/messageOStream.cpp message/messageOStream.h packer/packer.h packer/packerDefault.cpp packer/packerDefault.h netError.h acceptor/acceptorTcp.h connection/connection.h connection/connectionTcp.cpp connection/connectionTcp.h connection/connectionIO.h warehouse/warehouse.h cipher/cipher.h handler/eventHandler.h connection/endPoint.h)

###########################################################
# setting libraries

# shared
add_library(zam_net_shared SHARED ${SOURCE_FILES})
set_target_properties(zam_net_shared PROPERTIES OUTPUT_NAME net)

# dylib needs static libraries linkning
if(APPLE OR MSVC)
    set(DEPENDENT_LIBRARY_FILES zam_base_shared ${JSONCPP_LIBRARY} ${Boost_LIBRARIES})

    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")   # turn off deprecated warning (latest jsoncpp has lots of deprecated warning)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4819")   # trun off code page warning
        set(DEPENDENT_LIBRARY_FILES ${DEPENDENT_LIBRARY_FILES} Ws2_32)
    else(MSVC)
        set(DEPENDENT_LIBRARY_FILES ${DEPENDENT_LIBRARY_FILES} pthread)
    endif(MSVC)

    target_link_libraries (zam_net_shared ${DEPENDENT_LIBRARY_FILES})
endif()

# static
add_library(zam_net_static STATIC ${SOURCE_FILES})
set_target_properties(zam_net_static PROPERTIES OUTPUT_NAME net_static)

# additional static options
StaticCompile(zam_net_static)

###########################################################
# installing libraries

# lib files
install(TARGETS zam_net_shared DESTINATION ${ROOT_INSTALL_PATH}/lib)
install(TARGETS zam_net_static DESTINATION ${ROOT_INSTALL_PATH}/lib)


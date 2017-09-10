function(EnableMDFlag)
    set(CMAKE_USER_MAKE_RULES_OVERRIDE
            ${CMAKE_CURRENT_SOURCE_DIR}/c_flag_overrides_md.cmake)
    set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
            ${CMAKE_CURRENT_SOURCE_DIR}/cxx_flag_overrides_md.cmake)
endfunction()

function(EnableMTFlag)
    set(CMAKE_USER_MAKE_RULES_OVERRIDE
            ${CMAKE_CURRENT_SOURCE_DIR}/c_flag_overrides_mt.cmake)
    set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
            ${CMAKE_CURRENT_SOURCE_DIR}/cxx_flag_overrides_mt.cmake)
endfunction()
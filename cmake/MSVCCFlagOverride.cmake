function(EnableMDFlag)
    message("called EnableMDFlag")
    set(CMAKE_USER_MAKE_RULES_OVERRIDE
            cmake/c_flag_overrides_md.cmake)
    set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
            cmake/cxx_flag_overrides_md.cmake)
endfunction()

function(EnableMTFlag CMAKE_USER_MAKE_RULES_OVERRIDE)
    message("called EnableMTFlag")
    set(CMAKE_USER_MAKE_RULES_OVERRIDE
            cmake/c_flag_overrides_mt.cmake)
    set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
            cmake/cxx_flag_overrides_mt.cmake)
endfunction()
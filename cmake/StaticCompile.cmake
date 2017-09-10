function(StaticCompile target)
    if(MSVC)
        target_compile_options(${target}
                PUBLIC "/MT$<$<STREQUAL:$<CONFIGURATION>,Debug>:d>"
                )
    endif(MSVC)
endfunction()

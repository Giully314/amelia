add_library(amelia_print)

target_sources(amelia_print
    PUBLIC FILE_SET CXX_MODULES 
    FILES
        amelia_printf.cppm
)


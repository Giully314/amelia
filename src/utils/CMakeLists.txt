add_library(amelia_utils)

target_sources(amelia_utils
    PUBLIC
        amelia_utils.S

    PUBLIC FILE_SET CXX_MODULES 
    FILES 
        amelia_utils.cppm)

target_link_libraries(amelia_utils PRIVATE amelia_src)
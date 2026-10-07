add_library(amelia_ds)

target_sources(amelia_ds
    PUBLIC FILE_SET CXX_MODULES 
    FILES ameliads_stringview.cppm)

target_link_libraries(amelia_ds PRIVATE amelia_src)
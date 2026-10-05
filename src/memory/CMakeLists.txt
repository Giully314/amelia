add_library(amelia_memory)

target_sources(amelia_memory
    PUBLIC FILE_SET CXX_MODULES 
    FILES ameliamemory_mmio.cppm)

target_link_libraries(amelia_memory PRIVATE amelia_src)
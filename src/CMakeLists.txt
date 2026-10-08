add_library(amelia_src)

target_link_libraries(amelia_src INTERFACE amelia_compiler_flags)

target_sources(amelia_src     
    PUBLIC  
        memory.S 
    
    PUBLIC
    FILE_SET CXX_MODULES
    FILES  
    amelia_types.cppm
)


add_subdirectory(peripherals)
add_subdirectory(memory)
add_subdirectory(ds)
add_subdirectory(utils)
add_subdirectory(entry)
add_subdirectory(print)
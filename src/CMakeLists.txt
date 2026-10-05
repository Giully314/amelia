add_library(amelia_src)

target_link_libraries(amelia_src INTERFACE amelia_compiler_flags)

target_sources(amelia_src 
    PRIVATE
        boot.S
    
    PUBLIC  
        memory.S 
        utils.S

    PRIVATE
    FILE_SET private_modules TYPE CXX_MODULES
    FILES amelia_kernelmain.cppm 
    
    PUBLIC
    FILE_SET CXX_MODULES
    FILES  
    amelia_types.cppm
    amelia_utils.cppm
)


add_subdirectory(peripherals)
add_subdirectory(memory)
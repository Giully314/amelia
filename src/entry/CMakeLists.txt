add_library(amelia_entry)

target_sources(amelia_entry
    PRIVATE
        amelia_boot.S

    PRIVATE FILE_SET private_modules TYPE CXX_MODULES 
    FILES 
        amelia_kernelmain.cppm)


target_link_libraries(amelia_entry PRIVATE amelia_peripherals amelia_print amelia_utils)
target_include_directories(amelia_entry PRIVATE ${PROJECT_SOURCE_DIR}/src)
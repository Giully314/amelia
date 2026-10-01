add_library(amelia_src)

target_link_libraries(amelia_src INTERFACE amelia_compiler_flags)
target_include_directories(amelia_src PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_sources(amelia_src PRIVATE kernel_main.cpp memory.S boot.S)


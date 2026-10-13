add_library(amelia_entry)

target_sources(amelia_entry
    PRIVATE
        amelia_boot.S
        ameliaentry_exception_vector.S

    PRIVATE FILE_SET private_modules TYPE CXX_MODULES 
    FILES 
        amelia_kernelmain.cppm)


target_link_libraries(amelia_entry PRIVATE amelia_peripherals amelia_print amelia_utils amelia_exceptions)
target_include_directories(amelia_entry PRIVATE ${PROJECT_SOURCE_DIR}/src)

# Generate a header with sizes/offsets of C++ structs to be used in assembly files.
set(ASM_OFFSETS_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
set(ASM_OFFSETS_HEADER ${ASM_OFFSETS_DIR}/ameliaentry_asm_offsets.h)
set(ASM_OFFSETS_ASM ${ASM_OFFSETS_DIR}/ameliaentry_asm_offsets.s)
separate_arguments(ASM_OFFSETS_CXX_FLAGS UNIX_COMMAND "${CMAKE_CXX_FLAGS}")

add_custom_command(
    OUTPUT ${ASM_OFFSETS_HEADER}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${ASM_OFFSETS_DIR}
    COMMAND ${CMAKE_CXX_COMPILER} --target=${CMAKE_CXX_COMPILER_TARGET} ${ASM_OFFSETS_CXX_FLAGS}
            -std=c++26 -S -o ${ASM_OFFSETS_ASM} ${CMAKE_CURRENT_SOURCE_DIR}/ameliaentry_asm_offsets.cpp
    COMMAND ${CMAKE_COMMAND} -DINPUT=${ASM_OFFSETS_ASM} -DOUTPUT=${ASM_OFFSETS_HEADER}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/gen_asm_offsets.cmake
    DEPENDS ameliaentry_asm_offsets.cpp ameliaentry_exception_frame.hpp gen_asm_offsets.cmake
    COMMENT "Generating asm offsets header"
    VERBATIM)

target_sources(amelia_entry PRIVATE ${ASM_OFFSETS_HEADER})
target_include_directories(amelia_entry PRIVATE ${ASM_OFFSETS_DIR})

cmake_minimum_required(VERSION 4.2)

project(AMELIA DESCRIPTION "An operating system for rpi4 in C++" LANGUAGES CXX ASM)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(amelia_compiler_flags INTERFACE)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
target_compile_options(amelia_compiler_flags INTERFACE -Werror -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion -mcpu=cortex-a72+nosimd --target=aarch64-elf -ffreestanding -nostdlib)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
target_compile_options(amelia_compiler_flags INTERFACE -Werror -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion)
endif()

add_subdirectory(src)
add_subdirectory(app)
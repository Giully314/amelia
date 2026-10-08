set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_ASM_COMPILER clang)
set(CMAKE_LINKER ld.lld)

set(CMAKE_C_COMPILER_TARGET aarch64-none-elf)
set(CMAKE_CXX_COMPILER_TARGET aarch64-none-elf)
set(CMAKE_ASM_COMPILER_TARGET aarch64-none-elf)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# NOTE: the strict-align is necessary until the MMU is implemented, because an unaligned memory access causes a fault.
set(COMMON_FLAGS "-mcpu=cortex-a72 -mstrict-align -ffreestanding -fno-stack-protector -fno-pic")
set(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics")
set(CMAKE_ASM_FLAGS_INIT "${COMMON_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS_INIT "-nostdlib -fuse-ld=lld -static")
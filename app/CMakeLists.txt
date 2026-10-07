# Keep _start (in a static lib, otherwise unreferenced) from being dropped by the linker.
set(CMAKE_CXX_LINK_LIBRARY_USING_WHOLE_ARCHIVE "LINKER:--whole-archive" "<LINK_ITEM>" "LINKER:--no-whole-archive")
set(CMAKE_CXX_LINK_LIBRARY_USING_WHOLE_ARCHIVE_SUPPORTED TRUE)

add_executable(amelia_kernel_img main.cpp)
target_link_options(amelia_kernel_img PRIVATE -T ${CMAKE_SOURCE_DIR}/src/kernel.ld)
set_target_properties(amelia_kernel_img PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/src/kernel.ld)
target_link_libraries(amelia_kernel_img PRIVATE amelia_src amelia_peripherals amelia_ds amelia_memory amelia_utils $<LINK_LIBRARY:WHOLE_ARCHIVE,amelia_entry>)

set_target_properties(amelia_kernel_img PROPERTIES OUTPUT_NAME kernel8 SUFFIX .elf LINK_DEPENDS ${CMAKE_SOURCE_DIR}/src/kernel.ld)

add_custom_command(TARGET amelia_kernel_img POST_BUILD COMMAND llvm-objcopy -O binary $<TARGET_FILE:amelia_kernel_img> $<TARGET_FILE_DIR:amelia_kernel_img>/kernel8.img COMMENT "Creating kernel8.img")
/*
Linker script for loading the kernel at the right address.
*/

ENTRY (_start)

SECTIONS 
{
    . = 0x0;
    .text.ivt : {KEEP(*(.text.ivt))}
    kernel_img_begin = .;
    .text : { *(.text .text.*) }
    kernel_img_end = .;
    . = 0x80000;
    .text.boot : {KEEP(*(.text.boot))}
    .rodata : { *(.rodata .rodata.*) }
    .data : { *(.data .data.*) } 
    . = ALIGN(0x8);
    bss_begin = .;
    .bss : { *(.bss*) }
    bss_end = .;
}

first_memory_available = kernel_img_end;

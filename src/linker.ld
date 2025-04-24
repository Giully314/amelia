/*
Linker script for loading the kernel at the right address.
*/

ENTRY (_start)

SECTIONS 
{
    . = 0x0;
    .text.ivt : {KEEP(*(.text.ivt))}
    . = 0x80000;
    .text.boot : {KEEP(*(.text.boot))}
    .text : { *(.text .text.*) }
    .rodata : { *(.rodata .rodata.*) }
    .data : { *(.data .data.*) } 
    . = ALIGN(0x8);
    bss_begin = .;
    .bss : { *(.bss*) }
    bss_end = .;
}

/*
Linker script for loading the kernel at the right address.
*/

ENTRY (_start)

SECTIONS 
{
    /* . = 0x8000 */
    .text.boot : { *(.text.boot) }
    .text : { *(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) } 
    . = ALIGN(0x8);
    bss_begin = .;
    .bss : { *(.bss) }
    bss_end = .;
}


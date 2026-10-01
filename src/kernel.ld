/* kernel.ld

Linker script to put the kernel in the right memory addresses.
*/

ENTRY (_start)

SECTIONS
{ 
    /*AArch64 kernel load address.*/
    . = 0x80000; 
    .text : { KEEP(*(.text.boot)) *(.text .text.*) }
    .rodata : { *(.rodata .rodata.*)}
    .data : { *(.data .data.*)}
    . = ALIGN(16);
    bss_begin = .;
    .bss : { *(.bss) }
    bss_end = .;

    /DISCARD/ : { *(.comment) *(.gnu) *(.note) *(.eh_frame*)}
}

/* bss_size = (bss_end - bss_begin) >> 3; */
/*
Linker script for loading the kernel at the right address.
*/

ENTRY (_start)

SECTIONS 
{
    . = 0x0;
    /*Even if not referenced, keep the boot section and the interrupt vector table.*/ 
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

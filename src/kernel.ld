/*
Linker script for loading the kernel at the right address.
*/

ENTRY (_start)

SECTIONS 
{
    . = 0x80000;
    .text : { KEEP(*(.text.boot)) *(.text .text.*) }
    .rodata : { *(.rodata .rodata.*) }
    .data : { *(.data .data.*) } 
    . = ALIGN(16);
    bss_begin = .;
    .bss : { *(.bss*) }
    bss_end = .;

    /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}  
bss_size = (bss_end - bss_begin)>>3;

/* 
SECTIONS
{
    . = 0x80000;
    .text : { KEEP(*(.text.boot)) *(.text .text.* .gnu.linkonce.t*) }
    .rodata : { *(.rodata .rodata.* .gnu.linkonce.r*) }
    PROVIDE(_data = .);
    .data : { *(.data .data.* .gnu.linkonce.d*) }
    .bss (NOLOAD) : {
        . = ALIGN(16);
        bss_begin = .;
        *(.bss .bss.*)
        *(COMMON)
        bss_end = .;
    }
    _end = .;

   /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}
__bss_size = (bss_end - bss_begin)>>3; */
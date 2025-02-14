#include <amelia/memory.h>
// The kernel is loaded at 0x80000000. This file is placed at that position
// by the boot.ld script.
// This file is the first thing that get executed, it setup the stack and 
// calls start() in the start.c file.


.section .text.boot

.global _start  
_start: 
    // Load the state of the multiprocessor affinity register.
    // To access this special register we need a special instruction, mrs
    // https://developer.arm.com/documentation/dui0283/b/arm-and-thumb-instructions/miscellaneous-instructions/mrs
    // https://developer.arm.com/documentation/ddi0601/2024-12/AArch64-Registers/MPIDR-EL1--Multiprocessor-Affinity-Register
    // Because at startup each of the processor starts to execute the code, we must select
    // only one.
    // In this case we are interested to get the core id and choose on of the core
    // to start the execution (in this case the core with id 0).
    mrs x0, mpidr_el1
    and x0, x0, #0xFF
    cbz x0, master
    b proc_hang

proc_hang:
    b proc_hang

master:
    // memzero function accepts 2 args, start address of memory and size.
    // Note that in arm, the first 7 arguments passed to a function are passed
    // via the registers x0-x6.
    adr x0, bss_begin
    adr x1, bss_end
    sub x1, x1, x0
    bl memzero

    mov sp, #LOW_MEMORY
    bl kernel_main    


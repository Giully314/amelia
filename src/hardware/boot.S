#include <amelia/memory.h>
// The kernel is loaded at 0x80000000. This file is placed at that position
// by the boot.ld script.
// This file is the first thing that get executed, it setup the stack and 
// calls start() in the start.c file.


.section ".text.boot"

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
    // https://developer.arm.com/documentation/ddi0500/j/System-Control/AArch64-register-descriptions/Multiprocessor-Affinity-Register?lang=en
    mrs x0, mpidr_el1
    and x0, x0, #0x3
    mov x2, x0 // save the processor id
    // cbz x0, master
    cmp x0, #0x0
    beq init_bss
    
    // for all non primary processor, wait for 150 cycles.
    mov x0, #150
    bl delay
    b master

proc_hang:
    b proc_hang

init_bss:
    // memzero function accepts 2 ars, start address of memory and size.
    // Note that in arm, the first 7 arguments passed to a function are passed
    // via the registers x0-x6.
    adr x0, bss_begin
    adr x1, bss_end
    sub x1, x1, x0
    bl memzero
    b master

// Requires x0 to have the processor id.
setup_stack:


// The master process is responsible to initialize the resources.
master:
    mov x0, x2
    mov x1, #STACK_SIZE
    // Compute the right start of the stack for each processor.
    mul x1, x0, x1 
    add x1, x1, #LOW_MEMORY
    mov sp, x1 
    # Pass processor id stored in x0 to kernel_main.
    bl kernel_main
    b proc_hang // should never come here.


// https://github.com/s-matyukevich/raspberry-pi-os/issues/8#issuecomment-624115220
// Requires x0 with mpidr_el1.
// Requires x1 with starting address.
wakeup_core:
    mov x2, 0xd8
    str x1, [x2, x0, LSL #3]
    sev
    ret
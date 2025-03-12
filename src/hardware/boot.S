// The kernel is loaded at 0x80000000. This file is placed at that position
// by the boot.ld script.
// This file is the first thing that get executed, it setup the stack and 
// calls start() in the start.c file.

#include <amelia/memory.h>
#include <amelia/arm/sysregs.h>

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
    beq master
    
    // for all non primary processor, wait for 150 cycles.
    // mov x0, #150
    // bl delay
    b proc_hang

proc_hang:
    b proc_hang



// The master process is responsible to initialize the state of the OS such as EL, stack and wake up other cores.
master:
    // Set the system control register (el1). Configure parameters such as cache access, MMU and it 
    // accessible from >= el1. 
    // Page 2654 of the ARM v8 manual.
    ldr x0, =SCTLR_EL1_VALUE_MMU_DISABLED
    msr sctlr_el1, x0

    // Set the hypervisor configuration register el2.
    ldr x0, =HCR_EL2_VALUE
    msr hcr_el2, x0

    ldr x0, =SCR_EL3_VALUE
    msr scr_el3, x0

    // Set the program status register.
    ldr x0, =SPSR_EL3_VALUE
    msr spsr_el3, x0

    // elr_el3 holds the address of the instruction to be executed after eret.
    adr x0, el1_entry
    msr elr_el3, x0

    eret

el1_entry:
    bl init_bss

    mrs x0, mpidr_el1
    and x0, x0, #0x3
    mov x1, #STACK_SIZE
    // Compute the right start of the stack for each processor.
    mul x1, x0, x1 
    add x1, x1, #LOW_MEMORY
    mov sp, x1 
    # Pass processor id stored in x0 to kernel_main.
    bl kernel_main
    b proc_hang // should never come here.

init_bss:
    // memzero function accepts 2 args, start address of memory and size.
    adr x0, bss_begin
    adr x1, bss_end
    sub x1, x1, x0
    // Save link register into x3. Stack is not yet initialized.
    mov x3, lr
    bl memzero
    mov lr, x3
    ret
    



// https://github.com/s-matyukevich/raspberry-pi-os/issues/8#issuecomment-624115220
// Requires x0 with mpidr_el1.
// Requires x1 with starting address.
wakeup_core:
    mov x2, 0xd8
    str x1, [x2, x0, LSL #3]
    sev
    ret
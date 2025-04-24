// src/hardware/boot.S
// DESCRIPTION:
//  The kernel is loaded at 0x80000000. This file is placed at that position
//  by the linker.ld script.
//  The job of this file is to execute initialization steps for the machine like:
//  1) EL3 -> EL2 -> EL1 setup.
//  2) Setup bss section.
//  3) Setup the stack.
//  4) Call kernel_init defined in kernel_start.c.
//  5) Call kernel_main defined in kernel_start.c.
//  
//  For now there is only one core active, the rest just hang in a loop.
//  For more information check doc/boot.md.

#include <amelia/hardware/platform_config.hpp>
#include <amelia/arm/sysregs.hpp>

.section ".text.boot"

.globl _start  
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
    bl get_processor_id
    cbz x0, master
    
    // for all non primary processors.
    b proc_hang

proc_hang:
    b proc_hang

// The master process is responsible to initialize the state of the OS such as EL, stack 
// and (in future) wake up other cores.
master:
    // Set the system control register (el1). Configure parameters such as cache access, MMU and it 
    // accessible from >= el1. 
    // Page 2654 of the ARM v8 manual.
    ldr x0, =SCTLR_EL1_VALUE_MMU_DISABLED
    msr sctlr_el1, x0

    // Enable simd and fp registers in el1. These registers
    // are used by the compiler in printf.
    ldr x0, =CPACR_VALUE
    msr cpacr_el1, x0

    // Set the hypervisor configuration register el2.
    ldr x0, =HCR_EL2_VALUE
    msr hcr_el2, x0

    ldr x0, =SCR_EL3_VALUE
    msr scr_el3, x0

    // Set the program status register.
    ldr x0, =SPSR_EL3_VALUE
    msr spsr_el3, x0

    // Set the interrupt vector table address.
    ldr x0, =INT_VEC_TABLE_ADDRESS
    msr vbar_el1, x0

    // elr_el3 holds the address of the instruction to be executed after eret.
    adr x0, el2_entry
    msr elr_el3, x0

    eret


el2_entry:
    // Set the program status register.
    ldr x0, =SPSR_EL2_VALUE
    msr spsr_el2, x0

    // elr_el2 holds the address of the instruction to be executed after eret.
    adr x0, el1_entry
    msr elr_el2, x0

    eret

el1_entry:
    bl get_processor_id
    // Save core id for future use in this routine.
    mov x19, x0
    bl init_stack
    bl init_bss

    mov x0, x19
    bl kernel_entry_point 

    // reset the stack for the call to kernel_main.
    // mov x0, x19 
    // bl init_stack

    // mov x0, x19 
    //    
    // Start kernel main point.
    //bl kernel_main
    b proc_hang // should never come here.


// TODO: because I'm using QEMU, the load address of the kernel is 0x80000.
// Because LOW_MEMORY is 0x40000, if we use the second core, would overwrite the content of the kernel memory region.
// That's why, enabling other cores should be done after the implementation of virtual memory setup by the core 0.
// Setup the stack based on the processor id.
// x0 must contain the processor id.
init_stack:
    mov x1, #STACK_SIZE
    // Compute the right start of the stack for each processor based on the id.
    mul x1, x0, x1 
    add x1, x1, #LOW_MEMORY
    mov sp, x1
    ret

init_bss:
    // memzero function accepts 2 args, start address of memory and size.
    adr x0, bss_begin
    adr x1, bss_end
    sub x1, x1, x0
    // Save link register.
    str lr, [sp, #-16]!
    bl memzero
    ldr lr, [sp], #16
    ret


// https://github.com/s-matyukevich/raspberry-pi-os/issues/8#issuecomment-624115220
// Requires x0 with mpidr_el1.
// Requires x1 with starting address.
wakeup_core:
    mov x2, 0xd8
    str x1, [x2, x0, LSL #3]
    sev
    ret

// Get processor id.
// The result is saved in x0.
get_processor_id:
    mrs x0, mpidr_el1
    and x0, x0, #0x3
    ret
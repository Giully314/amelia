#include <arm/ameliaarm_sysregister_values.hpp>

.section ".text.boot"

.global _start


// The code is executed on all the cores, so we need to take only 1 core to execute the initial setup and 
// make the others in idle state.
_start:
    mrs x0, mpidr_el1
    and x0, x0, #3
    cbz x0, main_core
    b idle


// "secondary" core, idle.
idle:  
    wfe // wait for event, idle core state.
    b idle

// Main core, execute init setup and switch to el2.
// Note that this could function only in qemu or if we use a rpi4 we need to set the setting
// to start from el3 in the config.txt. The el3 starts only with the gpu which executes the boot
// process and then before the start of the kernel it switches to el2.
main_core:
    ldr x0, =SCTLR_EL1_VALUE
    msr sctlr_el1, x0 

    ldr x0, =HCR_EL2_VALUE
    msr hcr_el2, x0 

    ldr x0, =SCR_EL3_VALUE
    msr scr_el3, x0

    ldr x0, =SPSR_EL3_VALUE
    msr spsr_el3, x0

    ldr x0, =CPTR_EL2_VALUE
    msr cptr_el2, x0

    ldr x0, =CPACR_EL1_VALUE
    msr cpacr_el1, x0

    adr x0, el2_entry
    msr elr_el3, x0 

    eret


// Initialize system hardware resources at el2. This isn't really necessary
// if we don't use os virtualization.
el2_entry:
    // Set the stack pointer below the _start code.
    ldr x0, =_start
    mov sp, x0

    // Clean BSS
    ldr x0, =bss_begin
    ldr x1, =bss_end
    sub x1, x1, x0
    bl memzero

    bl kernel_init

    ldr x0, =SPSR_EL2_VALUE
    msr spsr_el2, x0

    adr x0, el1_entry
    msr elr_el2, x0

    eret

// Kernel entry point at el1.
el1_entry:
    // Set the stack pointer below the _start code.
    ldr x0, =_start
    mov sp, x0

    bl kernel_main 

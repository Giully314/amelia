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

// Main core, execute init setup.
main_core:
    // Set the stack pointer below the _start code.
    ldr x0, =_start
    mov sp, x1

    // Clean BSS
    ldr x0, =bss_begin
    ldr x1, =bss_end
    sub x1, x1, x0
    bl memzero

    bl kernel_main 

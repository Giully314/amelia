// src/kernel/scheduler.S
// DESCRIPTION: Define low level scheduling routines.

#include <amelia/kernel/scheduler.h>

.global scheduler_cpu_switch_to
scheduler_cpu_switch_to:
    mov x10, #THREAD_CPU_CONTEXT
    // Store the registers of the current task in the CPUContext struct
    // before switch.
    add x8, x0, x10
    mov x9, sp
    
    stp x19, x20, [x8], #16
    stp x21, x22, [x8], #16
    stp x23, x24, [x8], #16
    stp x25, x26, [x8], #16
    stp x27, x28, [x8], #16
    stp  d8,  d9, [x8], #16
    stp d10, d11, [x8], #16
    stp d12, d13, [x8], #16
    stp d14, d15, [x8], #16

    stp x29, x9, [x8], #16
    str x30, [x8] // The link register (x30) is stored as pc in the struct.
    
    // Load the registers from the CPUContext struct of the next
    // task that must be executed.
    add x8, x1, x10
    ldp x19, x20, [x8], #16
    ldp x21, x22, [x8], #16
    ldp x23, x24, [x8], #16
    ldp x25, x26, [x8], #16
    ldp x27, x28, [x8], #16
    ldp  d8,  d9, [x8], #16
    ldp d10, d11, [x8], #16
    ldp d12, d13, [x8], #16
    ldp d14, d15, [x8], #16
    
    ldp x29, x9, [x8], #16
    ldr x30, [x8] 
    mov sp, x9

    ret


.global ret_from_fork
ret_from_fork:
    bl scheduler_schedule_tail // defined in scheduler.c
    // In the fork operation (could be a start_task, copy or anything related
    // to creating a new task for the scheduler) we setup the x19 register with
    // the address of the function to execute and the x20 register with a pointer
    // to the arg to pass to the function.
    mov x0, x20
    blr x19 // Should never return.
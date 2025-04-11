// src/hardware/exception_entry.S
// DESCRIPTION: 
//  Defines the basic building blocks for handling exceptions.

#include <amelia/hardware/exception_entry.h>
#include <amelia/arm/sysregs.h>
#include <amelia/kernel/syscall.h>

// Define a macro helper for exception entry.
.macro ventry label
.align 7
b \label
.endm

// Hadler macro for invalid entry. 
// We prepare 3 arguments and call show_invalid_entry_msg.
// The esr_el1 (exception syndrome register for el1) holds information
// about the exception.
// The elr_el1 (exception link register for el1) holds the address of the 
// instruction to execute after the exception is handled.
.macro handle_invalid_entry el type
kernel_entry \el
mov x0, #\type
mrs x1, esr_el1
mrs x2, elr_el1
bl show_invalid_entry_msg
b err_hang
.endm 

.section .text

// Infinite loop after error.
.global err_hang
err_hang:
    b err_hang

// TODO: save the state of SIMD and FP registers.
// Save the state of the registers onto the stack before jumping
// in the exception.
.macro kernel_entry el
sub sp, sp, #STACK_FRAME_SIZE
stp x0, x1,   [sp, #16 * 0]
stp x2, x3,   [sp, #16 * 1]
stp x4, x5,   [sp, #16 * 2]
stp x6, x7,   [sp, #16 * 3]
stp x8, x9,   [sp, #16 * 4]
stp x10, x11, [sp, #16 * 5]
stp x12, x13, [sp, #16 * 6]
stp x14, x15, [sp, #16 * 7]
stp x16, x17, [sp, #16 * 8]
stp x18, x19, [sp, #16 * 9]
stp x20, x21, [sp, #16 * 10]
stp x22, x23, [sp, #16 * 11]
stp x24, x25, [sp, #16 * 12]
stp x26, x27, [sp, #16 * 13]
stp x28, x29, [sp, #16 * 14]

// If we are in el0, we need to use the stack pointer of el0, so save it.
.if \el == 0
mrs x21, sp_el0
.else
add x21, sp, #STACK_FRAME_SIZE
.endif // \el == 0

// Save the register for interrupt recovery (eret).
mrs x22, elr_el1
mrs x23, spsr_el1

stp x30, x21, [sp, #16 * 15]
stp x22, x23, [sp, #16 * 16]

stp d0, d1,   [sp, #16 * 17]
stp d2, d3,   [sp, #16 * 18]
stp d4, d5,   [sp, #16 * 19]
stp d6, d7,   [sp, #16 * 20]
stp d8, d9,   [sp, #16 * 21]
stp d10, d11, [sp, #16 * 22]
stp d12, d13, [sp, #16 * 23]
stp d14, d15, [sp, #16 * 24]
.endm

// Restore the state of the registers after exception handling.
.macro kernel_exit el
ldp d0, d1,   [sp, #16 * 17]
ldp d2, d3,   [sp, #16 * 18]
ldp d4, d5,   [sp, #16 * 19]
ldp d6, d7,   [sp, #16 * 20]
ldp d8, d9,   [sp, #16 * 21]
ldp d10, d11, [sp, #16 * 22]
ldp d12, d13, [sp, #16 * 23]
ldp d14, d15, [sp, #16 * 24]

ldp x22, x23, [sp, #16 * 16]
ldp x30, x21, [sp, #16 * 15]

.if \el == 0
msr sp_el0, x21
.endif // \el == 0

// Restore the address and state for eret.
msr elr_el1, x22
msr spsr_el1, x23

ldp x0, x1,   [sp, #16 * 0]
ldp x2, x3,   [sp, #16 * 1]
ldp x4, x5,   [sp, #16 * 2]
ldp x6, x7,   [sp, #16 * 3]
ldp x8, x9,   [sp, #16 * 4]
ldp x10, x11, [sp, #16 * 5]
ldp x12, x13, [sp, #16 * 6]
ldp x14, x15, [sp, #16 * 7]
ldp x16, x17, [sp, #16 * 8]
ldp x18, x19, [sp, #16 * 9]
ldp x20, x21, [sp, #16 * 10]
ldp x22, x23, [sp, #16 * 11]
ldp x24, x25, [sp, #16 * 12]
ldp x26, x27, [sp, #16 * 13]
ldp x28, x29, [sp, #16 * 14]
add sp, sp, #STACK_FRAME_SIZE
eret
.endm


// Exception vectors.
.align 11
.global vectors
vectors:
    ventry sync_invalid_el1t    // sync el1t
    ventry irq_invalid_el1t     // irq el1t
    ventry fiq_invalid_el1t     // fiq el1t
    ventry serror_invalid_el1t  // error el1t

    ventry sync_invalid_el1h    // sync el1h
    ventry el1_irq              // irq el1h
    ventry fiq_invalid_el1h     // fiq el1h
    ventry serror_invalid_el1h  // error el1h

    ventry el0_sync                 // sync 64-bit el0
    ventry el0_irq                  // irq 64-bit el0
    ventry fiq_invalid_el0_64       // fiq 64-bit el0
    ventry serror_invalid_el0_64    // error 64-bit el0

    ventry sync_invalid_el0_32      // sync 32-bit el0
    ventry irq_invalid_el0_32       // irq 32-bit el0
    ventry fiq_invalid_el0_32       // fiq 32-bit el0
    ventry serror_invalid_el0_32    // error 32-bit el0


sync_invalid_el1t:
    handle_invalid_entry 1 SYNC_INVALID_EL1t

irq_invalid_el1t:
    handle_invalid_entry 1 IRQ_INVALID_EL1t

fiq_invalid_el1t:
    handle_invalid_entry 1 FIQ_INVALID_EL1t

serror_invalid_el1t:
    handle_invalid_entry 1 SERROR_INVALID_EL1t

sync_invalid_el1h:
    handle_invalid_entry 1 SYNC_INVALID_EL1h

irq_invalid_el1h:
    handle_invalid_entry 1 IRQ_INVALID_EL1h

fiq_invalid_el1h:
    handle_invalid_entry 1 FIQ_INVALID_EL1h

serror_invalid_el1h:
    handle_invalid_entry 1 SERROR_INVALID_EL1h

sync_invalid_el0_64:
    handle_invalid_entry 0 SYNC_INVALID_EL0_64

irq_invalid_el0_64:
    handle_invalid_entry 0 IRQ_INVALID_EL0_64

fiq_invalid_el0_64:
    handle_invalid_entry 0 FIQ_INVALID_EL0_64 

serror_invalid_el0_64:
    handle_invalid_entry 0 SERROR_INVALID_EL0_64 

sync_invalid_el0_32:
    handle_invalid_entry 0 SYNC_INVALID_EL0_32 

irq_invalid_el0_32:
    handle_invalid_entry 0 IRQ_INVALID_EL0_32 

fiq_invalid_el0_32:
    handle_invalid_entry 0 FIQ_INVALID_EL0_32 

serror_invalid_el0_32:
    handle_invalid_entry 0 SERROR_INVALID_EL0_32 

// interrupt procedure for eli1h irq.
el1_irq:
    kernel_entry 1
    bl irq_handle
    kernel_exit 1


el0_irq:
    kernel_entry 0
    bl irq_handle
    kernel_exit 0

// interrupt procedure for sync el0 64-bit.
// The ESR_EL1 (exception syndrome register el1) contains information
// about the exception generated. In this case we need to check if the exception
// is generated by a svc call.
el0_sync:
    kernel_entry 0
    mrs x25, esr_el1 // read the syndrome register 
    lsr x24, x25, #ESR_ELx_EC_SHIFT 
    cmp x24, #ESR_ELx_EC_SVC64 // check if the exception is raised from svc.
    b.eq el0_svc 
    handle_invalid_entry 0, SYNC_ERROR // if not crashes the system, right now no support for this.

sc_nr .req x25 // number of system calls
scno  .req x26 // syscall number
stbl  .req x27 // syscall table pointer

el0_svc:
    adr stbl, sys_call_table
    uxtw scno, w8  // zero extending w8 into scno register
    mov sc_nr, #__NR_syscall
    bl irq_enable
    cmp scno, sc_nr
    b.hs ni_sys // check if the syscall number is greater or equal to upper limits, in case branch to error.

    // address in the syscall table, stbl + (scno << 3)
    ldr x16, [stbl, scno, lsl #3] 
    blr x16
    b ret_from_syscall

ni_sys:
    handle_invalid_entry 0, SYSCALL_ERROR

ret_from_syscall:
    bl irq_disable
    str x0, [sp, #S_X0] // returned x0.
    kernel_exit 0

.global ret_to_user
ret_to_user:
    bl irq_disable
    kernel_exit 0

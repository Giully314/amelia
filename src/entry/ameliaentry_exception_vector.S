// src/entry/ameliaentry_exception_vector.S



#include "ameliaentry_exception_vector.hpp"
#include "ameliaentry_asm_offsets.h"

.macro ventry label
.align 7
    b \label
.endm


.macro handle_invalid_entry type
    kernel_entry
    mov x0, #\type
    mrs x1, esr_el1 // exception syndrome register
    mrs x2, elr_el1 // exception link register
    bl show_invalid_entry_message
    b err_hang
.endm


.section .text

.global err_hang
err_hang:
    b err_hang

// TODO: add EL parameter
// The sub of the stack in linux is done in the ventry, because there are some checks done on the 
// overflow and on virtual memory.
.macro kernel_entry
    sub sp, sp, #S_EXCEPTION_FRAME_SIZE 
    stp x0, x1, [sp, 16 * 0]
    stp	x2, x3, [sp, #16 * 1]
    stp	x4, x5, [sp, #16 * 2]
    stp	x6, x7, [sp, #16 * 3]
    stp	x8, x9, [sp, #16 * 4]
    stp	x10, x11, [sp, #16 * 5]
    stp	x12, x13, [sp, #16 * 6]
    stp	x14, x15, [sp, #16 * 7]
    stp	x16, x17, [sp, #16 * 8]
    stp	x18, x19, [sp, #16 * 9]
    stp	x20, x21, [sp, #16 * 10]
    stp	x22, x23, [sp, #16 * 11]
    stp	x24, x25, [sp, #16 * 12]
    stp	x26, x27, [sp, #16 * 13]
    stp	x28, x29, [sp, #16 * 14]
    str	x30, [sp, #16 * 15] 
.endm


.macro kernel_exit
    ldp	x0, x1, [sp, #16 * 0]
	ldp	x2, x3, [sp, #16 * 1]
	ldp	x4, x5, [sp, #16 * 2]
	ldp	x6, x7, [sp, #16 * 3]
	ldp	x8, x9, [sp, #16 * 4]
	ldp	x10, x11, [sp, #16 * 5]
	ldp	x12, x13, [sp, #16 * 6]
	ldp	x14, x15, [sp, #16 * 7]
	ldp	x16, x17, [sp, #16 * 8]
	ldp	x18, x19, [sp, #16 * 9]
	ldp	x20, x21, [sp, #16 * 10]
	ldp	x22, x23, [sp, #16 * 11]
	ldp	x24, x25, [sp, #16 * 12]
	ldp	x26, x27, [sp, #16 * 13]
	ldp	x28, x29, [sp, #16 * 14]
	ldr	x30, [sp, #16 * 15] 
	add	sp, sp, #S_EXCEPTION_FRAME_SIZE
	eret
.endm


.align 11
.global vectors
vectors:
    ventry sync_invalid_el1t    // sync el1t
    ventry irq_invalid_el1t     // irq el1t
    ventry fiq_invalid_el1t     // fiq el1t
    ventry serror_invalid_el1t  // error el1t

    ventry sync_invalid_el1h    // sync el1h
    ventry irq_invalid_el1h              // irq el1h
    ventry fiq_invalid_el1h     // fiq el1h
    ventry serror_invalid_el1h  // error el1h

    ventry sync_invalid_el0_64      // sync 64-bit el0
    ventry irq_invalid_el0_64                  // irq 64-bit el0
    ventry fiq_invalid_el0_64       // fiq 64-bit el0
    ventry serror_invalid_el0_64    // error 64-bit el0

    ventry sync_invalid_el0_32      // sync 32-bit el0
    ventry irq_invalid_el0_32       // irq 32-bit el0
    ventry fiq_invalid_el0_32       // fiq 32-bit el0
    ventry serror_invalid_el0_32    // error 32-bit el0


sync_invalid_el1t:
    handle_invalid_entry SYNC_INVALID_EL1t

irq_invalid_el1t:
    handle_invalid_entry IRQ_INVALID_EL1t

fiq_invalid_el1t:
    handle_invalid_entry FIQ_INVALID_EL1t

serror_invalid_el1t:
    handle_invalid_entry SERROR_INVALID_EL1t


sync_invalid_el1h:
    handle_invalid_entry SYNC_INVALID_EL1h

irq_invalid_el1h:
    handle_invalid_entry IRQ_INVALID_EL1h

fiq_invalid_el1h:
    handle_invalid_entry FIQ_INVALID_EL1h

serror_invalid_el1h:
    handle_invalid_entry SERROR_INVALID_EL1h


sync_invalid_el0_64:
    handle_invalid_entry SYNC_INVALID_EL0_64

irq_invalid_el0_64:
    handle_invalid_entry IRQ_INVALID_EL0_64

fiq_invalid_el0_64:
    handle_invalid_entry FIQ_INVALID_EL0_64 

serror_invalid_el0_64:
    handle_invalid_entry SERROR_INVALID_EL0_64 


sync_invalid_el0_32:
    handle_invalid_entry SYNC_INVALID_EL0_32 

irq_invalid_el0_32:
    handle_invalid_entry IRQ_INVALID_EL0_32 

fiq_invalid_el0_32:
    handle_invalid_entry FIQ_INVALID_EL0_32 

serror_invalid_el0_32:
    handle_invalid_entry SERROR_INVALID_EL0_32 
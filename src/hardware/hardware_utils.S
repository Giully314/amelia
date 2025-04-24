// src/hardware/hardware_utils.S
// DESCRIPTION: Implementation of low level routines which access hardware
//  directly.

.section .text 

.globl delay
delay:
    subs x0, x0, #1
    bne delay
    ret

.globl mem_read32
mem_read32:
    ldr w0, [x0] 
    ret

.globl mem_write32
mem_write32:
    str w1, [x0]
    ret

.globl get_el
get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    and x0, x0, #3
    ret

.globl mem_set32
mem_set32:
    ldr w2, [x0]
    orr w2, w1, w2
    str w2, [x0]
    ret

.globl mem_clear32
mem_clear32:
    ldr w2, [x0]
    mvn w1, w1
    and w2, w1, w2
    str w2, [x0]
    ret

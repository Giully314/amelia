// utils.s
// PURPOSE: implementation of low level utilities accessing hardware.
.section .text

// The delay function is implemented by subtracting 1 by the time specified. 
.global delay
delay: 
    subs x0, x0, #1
    bne delay
    ret

// Write 32 bits to an address.
.global put32 
put32:
    str w1, [x0]
    ret


// Read the memory (32 bit) specified by the address inside x0.
.global get32
get32:
    ldr w0, [x0]
    ret

// Get the current Exception Level.
.global get_el
get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ret 

.global set32
set32:
    ldr w2, [x0]
    orr w2, w1, w2
    str w2, [x0]
    ret

.global clear32
clear32:
    ldr w2, [x0]
    mvn w1, w1
    and w2, w1, w2
    str w2, [x0]
    ret

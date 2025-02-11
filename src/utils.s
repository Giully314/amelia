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
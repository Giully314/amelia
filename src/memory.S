// src/memory.S
// DESCRIPTION:
//  Define low level functions for memory management.

.section .text
.global memzero
memzero:
    str xzr, [x0], #8
    // If `s` is specified, update the condition flag.
    subs x1, x1, #8
    b.gt memzero
    ret

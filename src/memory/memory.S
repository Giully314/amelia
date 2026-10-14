// src/memory.S
// DESCRIPTION:
//  Define low level functions for memory management.

.section .text
.global memzero

// TODO: What if size is 1 byte? Should we add a precondition on the size to be min 8 bytes 
// or to be aligned by 8?
// x0: start address.
// x1: size.
memzero:
    str xzr, [x0], #8
    // If `s` is specified, update the condition flag.
    subs x1, x1, #8
    b.gt memzero
    ret

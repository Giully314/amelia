// src/memory/memops.S 
// DESCRIPTION:
//  Implementation of low level memory routines.

.globl memzero
memzero:
    str xzr, [x0], #8
    // if `s` is specified, update the condition flag.
    subs x1, x1, #8
    b.gt memzero
    ret
// src/utils.S
// PURPOSE: Define low level util functions.
//  
// DESCRIPTION:
//  This file defines primitive functions which requires direct access to the hardware, like delay, read/write 32/64 bit and so on. The primitives for read/write
//  can be used also for MMIO(memory mapped input output) for peripherals.


.section .text


.global delay
// Wait for n clocks.
// x0: number of clocks to delay.
delay:
    subs x0, x0, #1
    bne delay
    ret


.global write32
// Write 32 bit value in a specific memory address. 
// x0: 64 bit address.
// w1: 32 bit value to write.
write32:
    str w1, [x0]
    ret


.global read32
// Read a 32 bit value from a specific memory address.
// x0: 64 bit address.
// Return: a 32 bit value.
read32:
    ldr w0, [x0]
    ret



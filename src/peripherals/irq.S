// src/peripherals/irq.S
// DESCRIPTION:
//  Access hardware level interrupt controls.

.section .text 

// For now we only mask IRQ.
.globl irq_enable
irq_enable:
    msr daifclr, #2
    ret

.globl irq_disable
irq_disable:
    msr daifset, #2
    ret 
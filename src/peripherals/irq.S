// src/peripherals/irq.S
// DESCRIPTION:
//  Define initialization of IRQ vector table and enable/disable of interrupts.

.section .text

// Setup vector table start address.
.global irq_init_vector_table
irq_init_vector_table:
    // load VBAR_EL1 with virtual vector table address
    adr x0, vectors  
    msr vbar_el1, x0
    ret

// For now we only mask IRQ.
.global irq_enable
irq_enable:
    msr daifclr, #2
    ret

.global irq_disable
irq_disable:
    msr daifset, #2
    ret 
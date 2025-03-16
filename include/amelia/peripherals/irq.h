// amelia/peripherals/irq.h
// PURPOSE: Define bit value for enabling/disabling interrupts.
// 
// DESCRIPTION:
//  For now we work only with IRQ, that's why in irq.S we set 2 as a value for 
//  the DAIF register. 
//  D (bit 9): debug exception masked if set to 1.
//  A (bit 8): SError exception masked if set to 1.
//  I (bit 7): IRQ exception masked if set to 1.
//  F (bit 6): FIQ exception masked if set to 1.
//  Using daifclr and daifset we can clear/set directly the bits using values
//  for the first 4 bits. Set is used for masking the exceptions.
//  

#ifndef _AMELIA_PERIPHERALS_IRQ_H
#define _AMELIA_PERIPHERALS_IRQ_H

#include <amelia/peripherals/peripherals_base.h>

// Register for current pending interrupts.
#define IRQ_BASIC_PENDING_REG (PERIPHERALS_IRQ_START + 0x200)
#define IRQ_PENDING_REG1 (PERIPHERALS_IRQ_START + 0x204)
#define IRQ_PENDING_REG2 (PERIPHERALS_IRQ_START + 0x208)

#define IRQ_ENABLE_REG1_CORE0 (PERIPHERALS_IRQ_START + 0x210)
#define IRQ_ENABLE_REG2_CORE0 (PERIPHERALS_IRQ_START + 0x214)
// Local interrupts.
#define IRQ_ENABLE_BASIC_CORE0 (PERIPHERALS_IRQ_START + 0x218)


#define IRQ_SYSTEM_TIMER_0 (1 << 0)
#define IRQ_SYSTEM_TIMER_1 (1 << 1)
#define IRQ_SYSTEM_TIMER_2 (1 << 2)
#define IRQ_SYSTEM_TIMER_3 (1 << 3)

#ifndef __ASSEMBLER__ 


void irq_init_vector_table();

void irq_enable();
void irq_disable();

void irq_enable_interrupt_controller();


#endif 

#endif // _AMELIA_PERIPHERALS_IRQ_H
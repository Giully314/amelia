// amelia/peripherals/irq.h
// PURPOSE: Define API for interrupts.
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
//  Masking an interrupt means that the interrupt is ignored by the CPU.
//

#ifndef _AMELIA_PERIPHERALS_IRQ_H
#define _AMELIA_PERIPHERALS_IRQ_H

#include <amelia/basic_types.h>

// Set the address of the vector table.
void irq_init_vector_table();

// Enable interrupts by clearing the mask.
void irq_enable();

// Disable the interrupt by setting the mask.
void irq_disable();

// Enable global interrupt controller.
// irq_to_enable is a value where a bit is set to 1 if the corresponding
// interrupt must be enabled.
void irq_enable_interrupt_controller(u32 irq_to_enable);

// Enable all supported interrupts.
void irq_enable_all_interrupts();

#endif // _AMELIA_PERIPHERALS_IRQ_H
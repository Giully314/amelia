// amelia/peripherals/peripherals_base.h
// PURPOSE: define base info for all the peripherals.
//
// DESCRIPTION:
//  This file describes the base informations needed by all the periphals
//  such as memory start point.
//  These informations can be bound looking at the board manual BCM2837 ARM Peripherals.
//  The start memory for peripherals depends on if we access memory directly or
//  using the bus.
//

#ifndef _AMELIA_PERIPHERALS_BASE_H
#define _AMELIA_PERIPHERALS_BASE_H

// section 1.2.3
#define PERIPHERALS_MEMORY_START 0x3f000000

// section 7.5
// In the section the base address is reported as 0x7e00b000
// but we use 3f for the arguments discussed in 1.2.3
#define PERIPHERALS_IRQ_START 0x3f00b000

// section 12 of the board manual.
#define PERIPHERALS_SYSTEM_TIMER_START 0x3f003000

// Memory base for the local irq.
#define LOCAL_IRQ_START 0x40000000

#endif // _AMELIA_PERIPHERALS_BASE_H

// amelia/peripherals/local_irq_regs.h
// PURPOSE: Define local irq registers for each core.
//
// DESCRIPTION:
//  More on https://datasheets.raspberrypi.com/bcm2836/bcm2836-peripherals.pdf
//

#ifndef _AMELIA_PERIPHERALS_LOCAL_IRQ_REGS_H
#define _AMELIA_PERIPHERALS_LOCAL_IRQ_REGS_H

#include <amelia/peripherals/peripherals_base.h>

// local irq register for core 0.
#define CORE0_INTERRUPT_SOURCE (LOCAL_IRQ_START + 0x60)

#define LOCAL_TIMER_IRQ (1 << 11)

#endif // _AMELIA_PERIPHERALS_LOCAL_IRQ_REGS_H
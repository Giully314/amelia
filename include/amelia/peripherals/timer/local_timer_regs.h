// amelia/peripherals/timer/local_timer_regs.h
// PURPOSE: Define registers and values for the ARM timer.
//
// DESCRIPTION:
//  The registers defined are only for core 0.
//  More information here: https://datasheets.raspberrypi.com/bcm2836/bcm2836-peripherals.pdf
//

#ifndef _AMELIA_PERIPHERALS_LOCAL_TIMER_REGS_H
#define _AMELIA_PERIPHERALS_LOCAL_TIMER_REGS_H

#include <amelia/peripherals/peripherals_base.h>

#define LOCAL_TIMER_CONTROL_STATUS (LOCAL_IRQ_START + 0x34)

#define LOCAL_TIMER_IRQ_CLEAR_RELOAD (LOCAL_IRQ_START + 0x38)

#define LOCAL_TIMER_INTERRUPT_ENABLE (1 << 29)
#define LOCAL_TIMER_ENABLE (1 << 28)

#define LOCAL_TIMER_INTERRUPT_CLEAR (1 << 31)

#endif // _AMELIA_PERIPHERALS_LOCAL_TIMER_REGS_H
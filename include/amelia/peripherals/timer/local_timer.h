// amelia/peripherals/local_timer.h
// PURPOSE: Define API for the ARM (local) timer.
//
// DESCRIPTION:
//\

#ifndef _AMELIA_PERIPHERALS_LOCAL_TIMER_H
#define _AMELIA_PERIPHERALS_LOCAL_TIMER_H

// Initialize local timer.
void local_timer_init();

// Enable local timer.
void local_timer_enable_irq();

// Disable local timer;
void local_timer_disable_irq();

// Interrupt handler for local timer.
void local_timer_handle_irq();

#endif // _AMELIA_PERIPHERALS_LOCAL_TIMER_H
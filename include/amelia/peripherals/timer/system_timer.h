// amelia/peripherals/timer/system_timer.h
// PURPOSE: Define system timer API.
//
// DESCRIPTION:
//

#ifndef _AMELIA_PERIPHERALS_SYSTEM_TIMER_H
#define _AMELIA_PERIPHERALS_SYSTEM_TIMER_H

// Initialize timer.
void system_timer_init();

// handle timer interrupt.
void system_timer_handle_irq();

#endif // _AMELIA_PERIPHERALS_SYSTEM_TIMER_H

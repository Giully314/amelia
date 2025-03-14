// amelia/peripherals/timer.h
// PURPOSE: Define system timer API and values.
// 
// DESCRIPTION:
//  This file defines values found in the board manual in section 12.
//

#ifndef _AMELIA_PERIPHERALS_TIMER_H
#define _AMELIA_PERIPHERALS_TIMER_H

#include <amelia/peripherals/peripherals_base.h>

// The following are defined in section 12.1

// System timer control status
#define SYSTEM_TIMER_CS (PERIPHERALS_SYSTEM_TIMER_START + 0x0)

// system timer counter lower
#define SYSTEM_TIMER_CLO (PERIPHERALS_SYSTEM_TIMER_START + 0x4)

// system timer counter upper
#define SYSTEM_TIMER_CHI (PERIPHERALS_SYSTEM_TIMER_START + 0x8)

// The compare registers hold a value. When this value matches
// the counter, an interrupt is fired.
#define SYSTEM_TIMER_C0 (PERIPHERALS_SYSTEM_TIMER_START + 0Xc)
#define SYSTEM_TIMER_C1 (PERIPHERALS_SYSTEM_TIMER_START + 0X10)
#define SYSTEM_TIMER_C2 (PERIPHERALS_SYSTEM_TIMER_START + 0X14)
#define SYSTEM_TIMER_C3 (PERIPHERALS_SYSTEM_TIMER_START + 0X18)


// Set values for SYSTEM_TIMER_CS
// When the bit is set, it indicates a match detected (ackowledge).
#define SYSTEM_TIMER_CS_M0 (1 << 0)
#define SYSTEM_TIMER_CS_M1 (1 << 1)
#define SYSTEM_TIMER_CS_M2 (1 << 2)
#define SYSTEM_TIMER_CS_M3 (1 << 3)

// Initialize timer.
void timer_init();

// handle timer interrupt.
void timer_handle_irq();

#endif // _AMELIA_PERIPHERALS_TIMER_H

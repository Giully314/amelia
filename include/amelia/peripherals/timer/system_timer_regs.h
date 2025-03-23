// amelia/peripherals/timer/system_timer_regs.h
// PURPOSE: Define registers and values for the system timer.
//
// DESCRIPTION:
//  This file defines the registers and values for the system timer;
//  documentation can be found in section 12 of the board manual.
//

#ifndef _AMELIA_PERIPHERALS_SYSTEM_TIMER_REGS_H
#define _AMELIA_PERIPHERALS_SYSTEM_TIMER_REGS_H

#include <amelia/peripherals/peripherals_base.h>

// System timer control status
#define SYSTEM_TIMER_CS (PERIPHERALS_SYSTEM_TIMER_START + 0x0)

// system timer counter lower
#define SYSTEM_TIMER_CLO (PERIPHERALS_SYSTEM_TIMER_START + 0x4)

// system timer counter upper
#define SYSTEM_TIMER_CHI (PERIPHERALS_SYSTEM_TIMER_START + 0x8)

// The compare registers hold a value. When this value matches
// the counter, an interrupt is fired.
#define SYSTEM_TIMER_C0 (PERIPHERALS_SYSTEM_TIMER_START + 0xc)
#define SYSTEM_TIMER_C1 (PERIPHERALS_SYSTEM_TIMER_START + 0x10)
#define SYSTEM_TIMER_C2 (PERIPHERALS_SYSTEM_TIMER_START + 0x14)
#define SYSTEM_TIMER_C3 (PERIPHERALS_SYSTEM_TIMER_START + 0x18)

// Set values for SYSTEM_TIMER_CS
// When the bit is set, it indicates a match detected (ackowledge).
#define SYSTEM_TIMER_CS_M0 (1 << 0)
#define SYSTEM_TIMER_CS_M1 (1 << 1)
#define SYSTEM_TIMER_CS_M2 (1 << 2)
#define SYSTEM_TIMER_CS_M3 (1 << 3)

#endif // _AMELIA_PERIPHERALS_SYSTEM_TIMER_REGS_H

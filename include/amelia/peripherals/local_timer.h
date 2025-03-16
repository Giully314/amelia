// amelia/peripherals/local_timer.h
// PURPOSE: Define values for local (ARM) timer.
//
// DESCRIPTION:
//  Section 14 of the manual.
// https://datasheets.raspberrypi.com/bcm2836/bcm2836-peripherals.pdf


#ifndef _AMELIA_PERIPHERALS_LOCAL_TIMER_H
#define _AMELIA_PERIPHERALS_LOCAL_TIMER_H

#include <amelia/peripherals/peripherals_base.h>

#define LOCAL_TIMER_START 0x40000000

#define LOCAL_TIMER_CONTROL_STATUS (LOCAL_TIMER_START + 0x34)

#define LOCAL_TIMER_IRQ_CLEAR_RELOAD (LOCAL_TIMER_START + 0x38)

#define CORE0_INTERRUPT_SOURCE (LOCAL_TIMER_START + 0x60)


#define LOCAL_TIMER_INTERRUPT_ENABLE (1 << 29)
#define LOCAL_TIMER_ENABLE (1 << 28)
#define LOCAL_TIMER_VALUE (LOCAL_TIMER_INTERRUPT_ENABLE | LOCAL_TIMER_ENABLE)

#define LOCAL_TIMER_INTERRUPT_CLEAR (1 << 31)


// // Set the time for the timer to count down.
// #define LOCAL_TIMER_LOAD_REG (PERIPHERALS_IRQ_START + 0x400)

// // Read only. This register holds the current timer value and is counted 
// // down at each timer clock until 0 (then it restart from the value 
// // present in the LOAD register).
// #define LOCAL_TIMER_VALUE_REG (PERIPHERALS_IRQ_START + 0x404)

// #define LOCAL_TIMER_CONTROL_REG (PERIPHERALS_IRQ_START + 0x408)

// #define LOCAL_TIMER_IRQ_CLEAR_REG (PERIPHERALS_IRQ_START + 0x40c)

// #define LOCAL_TIMER_RAW_IRQ_REG (PERIPHERALS_IRQ_START + 0x410)

// #define LOCAL_TIMER_MASKED_IRQ_REG (PERIPHERALS_IRQ_START + 0x414)

// #define LOCAL_TIMER_RELOAD_REG (PERIPHERALS_IRQ_START + 0x418)

// TODO: pre-divider register and free running counter register. 


// Initialize local timer.
void local_timer_init();

// Interrupt handler for local timer.
void local_timer_handle_irq();

#endif // _AMELIA_PERIPHERALS_LOCAL_TIMER_H
// src/peripherals/timer/system_timer.c
#include <amelia/kernel/scheduler.h>
#include <amelia/peripherals/timer/system_timer.h>
#include <amelia/peripherals/timer/system_timer_regs.h>
#include <amelia/printf.h>
#include <amelia/utils.h>

// Set the interrupt interval.
static const unsigned int interval = 500000;

static unsigned int current_value = 0;

// Initialize the timer by setting one of the compare register for
// interrupt detection.
void system_timer_init()
{
	// Set the first timer interrupt to be after `interval` from current value.
	current_value = get32(SYSTEM_TIMER_CLO);
	current_value += interval;
	put32(SYSTEM_TIMER_C1, current_value);
}

// Handler for a timer interrupt.
void system_timer_handle_irq()
{
	current_value += interval;
	put32(SYSTEM_TIMER_C1, current_value);
	put32(SYSTEM_TIMER_CS, SYSTEM_TIMER_CS_M1);
	printf("Timer interrupt received\r\n");
	scheduler_timer_tick();
}
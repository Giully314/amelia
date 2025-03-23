// src/peripherals/timer/local_timer.c
#include <amelia/peripherals/timer/local_timer.h>
#include <amelia/peripherals/timer/local_timer_regs.h>
#include <amelia/printf.h>
#include <amelia/utils.h>

static const unsigned int interval = 200000;

void local_timer_enable_irq()
{
	u32 local_timer_setup = LOCAL_TIMER_INTERRUPT_ENABLE |
				LOCAL_TIMER_ENABLE;
	set32(LOCAL_TIMER_CONTROL_STATUS, local_timer_setup | interval);
}

void local_timer_disable_irq()
{
	u32 local_timer_setup = LOCAL_TIMER_INTERRUPT_ENABLE |
				LOCAL_TIMER_ENABLE;
	clear32(LOCAL_TIMER_CONTROL_STATUS, local_timer_setup | interval);
}

void local_timer_init()
{
	set32(LOCAL_TIMER_CONTROL_STATUS, interval);
}

void local_timer_handle_irq()
{
	// Clean interrupt pending bit.
	put32(LOCAL_TIMER_IRQ_CLEAR_RELOAD, LOCAL_TIMER_INTERRUPT_CLEAR);
	printf("Local timer interrupt.\r\n");
}
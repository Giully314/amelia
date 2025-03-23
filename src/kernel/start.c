// src/kernel/start.c
// DESCRIPTION: This file has methods for the start of the kernel.

#include <amelia/hardware/exception_entry.h>
#include <amelia/peripherals/irq.h>
#include <amelia/peripherals/irq_regs.h>
#include <amelia/peripherals/timer/local_timer.h>
#include <amelia/peripherals/timer/system_timer.h>
#include <amelia/peripherals/uart/mini_uart.h>
#include <amelia/printf.h>
#include <amelia/utils.h>

void putc(void *p, char c)
{
	mini_uart_send(c);
}

// Initialize all the resources. This function is executed at EL1.
void kernel_init(unsigned int processor_id)
{
	mini_uart_init();
	init_printf(0, putc);
	irq_init_vector_table();

	local_timer_init();
	system_timer_init();

	mini_uart_enable_irq();
	local_timer_enable_irq();

	irq_enable_interrupt_controller(IRQ_SYSTEM_TIMER_1);
	irq_enable();

	char id = processor_id + '0';
	printf("Kernel init from processor %c with current EL %u\n", id,
	       get_el());
}

// Kernel main, executed at EL1.
void kernel_main(unsigned int processor_id)
{
	char id = processor_id + '0';
	printf("Kernel main from processor %c with current EL %u\n", id,
	       get_el());

	while (1) {
		printf("%c", mini_uart_recv());
	}
}
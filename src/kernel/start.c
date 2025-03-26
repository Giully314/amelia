// src/kernel/start.c
// DESCRIPTION: This file has methods for the start of the kernel.

#include <amelia/hardware/exception_entry.h>
#include <amelia/kernel/fork.h>
#include <amelia/kernel/scheduler.h>
#include <amelia/memory.h>
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

	// mini_uart_enable_irq();
	local_timer_enable_irq();

	// irq_enable_interrupt_controller(IRQ_SYSTEM_TIMER_1);
	irq_enable_all_interrupts();
	irq_enable();

	scheduler_init();

	char id = processor_id + '0';
	printf("Kernel init from processor %c with current EL %u\n", id,
	       get_el());
}

void process(char *array)
{
	while (1) {
		for (int i = 0; i < 5; i++) {
			mini_uart_send(array[i]);
			delay(10000000);
		}
	}
}

// Kernel main, executed at EL1.
void kernel_main(unsigned int processor_id)
{
	local_timer_disable_irq();
	// irq_disable();

	char id = processor_id + '0';
	printf("Kernel main from processor %c with current EL %u\n", id,
	       get_el());

	i32 res = start_process((u64)&process, (u64) "12345");
	if (res != 0) {
		printf("error while starting process 1");
		return;
	}
	res = start_process((u64)&process, (u64) "abcde");
	if (res != 0) {
		printf("error while starting process 2");
		return;
	}

	while (1) {
		printf("SAMPLE\n");
		// delay(100000000);
		scheduler_schedule();
	}
}
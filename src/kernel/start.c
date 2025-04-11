// src/kernel/start.c
// DESCRIPTION: This file has methods for the start of the kernel.

#include <amelia/algorithms/comparators.h>
#include <amelia/ds/rb_tree.h>
#include <amelia/hardware/exception_entry.h>
#include <amelia/kernel/fork.h>
#include <amelia/kernel/scheduler.h>
#include <amelia/kernel/syscall.h>
#include <amelia/memory.h>
#include <amelia/memory/mblock.h>
#include <amelia/memory/page_allocator.h>
#include <amelia/memory/pool_allocator.h>
#include <amelia/peripherals/irq.h>
#include <amelia/peripherals/irq_regs.h>
#include <amelia/peripherals/timer/local_timer.h>
#include <amelia/peripherals/timer/system_timer.h>
#include <amelia/peripherals/uart/mini_uart.h>
#include <amelia/printf.h>
#include <amelia/user/stdio.h>
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
	for (int i = 0; i < 3; ++i) {
		for (int i = 0; i < 5; i++) {
			mini_uart_send(array[i]);
			delay(10000000);
		}
	}
}

void user_process1(char *array)
{
	char buf[2] = { 0 };
	while (1) {
		for (int i = 0; i < 5; i++) {
			buf[0] = array[i];
			write(buf);
			delay(100000);
		}
	}
}

void user_process()
{
	printf("HELLOO\n");
	char buf[30] = { 0 };
	tfp_sprintf(buf, "User process started\n\r");
	printf("HELLOOO\n");
	// write(buf);
	// u64 stack = (u64)page_malloc();
	// if (stack < 0) {
	// 	printf("Error while allocating stack for process 1\n\r");
	// 	return;
	// }
	// int err = sys_fork((u64)&user_process1, (u64) "12345", stack);
	// if (err < 0) {
	// 	printf("Error while clonning process 1\n\r");
	// 	return;
	// }

	// stack = (u64)page_malloc();
	// if (stack < 0) {
	// 	printf("Error while allocating stack for process 2\n\r");
	// 	return;
	// }
	// err = sys_fork((u64)&user_process1, (u64) "abcd", stack);
	// if (err < 0) {
	// 	printf("Error while clonning process 2\n\r");
	// 	return;
	// }
	// exit();
}

void kernel_process()
{
	printf("Kernel process started. EL %d\r\n", get_el());
	i32 err = move_to_user_mode((u64)&user_process);
	// if (err != 0) {
	// 	printf("Error while moving process to user mode\n\r");
	// }
	printf("moved to user mode\n");
	// while (1) {
	// }
}

// Kernel main, executed at EL1.
void kernel_main(unsigned int processor_id)
{
	local_timer_disable_irq();
	// irq_disable();

	char id = processor_id + '0';
	printf("Kernel main from processor %c with current EL %u\n", id,
	       get_el());

	while (1) {
		printf("SAMPLE\n");
		// delay(100000000);
		scheduler_schedule();
	}
}
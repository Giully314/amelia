// src/peripherals/irq.c
#include <amelia/basic_types.h>
#include <amelia/peripherals/aux.h>
#include <amelia/peripherals/irq.h>
#include <amelia/peripherals/irq_regs.h>
#include <amelia/peripherals/local_irq_regs.h>
#include <amelia/peripherals/timer/local_timer.h>
#include <amelia/peripherals/timer/system_timer.h>
#include <amelia/peripherals/timer/system_timer_regs.h>
#include <amelia/peripherals/uart/mini_uart.h>
#include <amelia/printf.h>
#include <amelia/utils.h>
// #include <amelia/peripherals/local_timer.h>

static const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",   "IRQ_INVALID_EL1t",
	"FIQ_INVALID_EL1t",    "ERROR_INVALID_EL1T",

	"SYNC_INVALID_EL1h",   "IRQ_INVALID_EL1h",
	"FIQ_INVALID_EL1h",    "ERROR_INVALID_EL1h",

	"SYNC_INVALID_EL0_64", "IRQ_INVALID_EL0_64",
	"FIQ_INVALID_EL0_64",  "ERROR_INVALID_EL0_64",

	"SYNC_INVALID_EL0_32", "IRQ_INVALID_EL0_32",
	"FIQ_INVALID_EL0_32",  "ERROR_INVALID_EL0_32"
};

// **************** LOCAL IRQ ***********************

static void irq_handle_local()
{
	u32 irq = get32(CORE0_INTERRUPT_SOURCE);
	switch (irq) {
	case LOCAL_TIMER_IRQ:
		local_timer_handle_irq();
		break;
	case 0:
		break;
	default:
		printf("Unkwown base pending irq: %x\r\n", irq);
	}
}

// ***************************************************

// Enable the IRQ on core 0.
void irq_enable_interrupt_controller(u32 irq_to_enable)
{
	put32(IRQ_ENABLE_REG1, irq_to_enable);
	// put32(LOCAL_TIMER_CONTROL_STATUS, LOCAL_TIMER_VALUE);
}

void irq_enable_all_interrupts()
{
	u32 irq_to_enable = IRQ_SYSTEM_TIMER_1 | IRQ_AUX;
	irq_enable_interrupt_controller(irq_to_enable);
}

// Handle IRQ.
void irq_handle()
{
	// For handling multiple interrupts in the same call,
	// wrap this in a loop.
	// Also the mechanism is not precise, because we need to
	// extract each bit with an AND to check.
	// printf("IRQ HANLDE");
	// switch (irq) {
	//     case (IRQ_SYSTEM_TIMER_1):
	//         // timer_handle_irq();
	//         break;
	//     default:
	//         printf("Unkwown pending irq: %x\r\n", irq);
	// }

	unsigned int irq = get32(IRQ_PENDING_REG1);
	if (irq & IRQ_SYSTEM_TIMER_1) {
		system_timer_handle_irq();
		irq &= ~IRQ_SYSTEM_TIMER_1;
	}
	if (irq & IRQ_AUX) {
		mini_uart_handle_irq();
		irq &= ~IRQ_AUX;
	}
	if (irq != 0) {
		printf("Unkwown base pending irq: %x\r\n", irq);
	}

	irq_handle_local();

	// irq = get32(AUX_IRQ);
	// switch (irq & 1) {
	// 	case 1:
	// 		mini_uart_handle_irq();
	// 		break;
	// }
}

// Temporary function for dealing with invalid (not supported) exceptions.
void show_invalid_entry_msg(int type, unsigned long esr, unsigned long address)
{
	printf("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr,
	       address);
}

// src/peripherals/irq.c
#include <amelia/peripherals/irq.h>
#include <amelia/utils.h>
#include <amelia/printf.h>
#include <amelia/peripherals/system_timer.h>
#include <amelia/peripherals/local_timer.h>
#include <amelia/peripherals/aux.h>
#include <amelia/peripherals/uart/mini_uart.h>

const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",		
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32"	
};


// Enable the IRQ on core 0.
void irq_enable_interrupt_controller() {
    put32(IRQ_ENABLE_REG1_CORE0, IRQ_SYSTEM_TIMER_1);
	// put32(LOCAL_TIMER_CONTROL_STATUS, LOCAL_TIMER_VALUE);
}

// Handle IRQ.
void irq_handle() {
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
		timer_handle_irq();
		irq &= ~IRQ_SYSTEM_TIMER_1;
	}
	else if (irq & (1 << 29)) {
		mini_uart_handle_irq();
		irq &= ~(1 << 29);
	}
	else if (irq) {
		printf("Unkwown base pending irq: %x\r\n", irq);
	}

	// irq = get32(AUX_IRQ);
	// switch (irq & 1) {
	// 	case 1:
	// 		mini_uart_handle_irq();
	// 		break;
	// }

	// Check for local interrupts.
	// irq = get32(CORE0_INTERRUPT_SOURCE);
	// switch (irq) {
	// 	case (1 << 11):
	// 		local_timer_handle_irq();
	// 		break;
	// 	default:
	// 		printf("Unkwown base pending irq: %x\r\n", irq);
	// }
}

// Temporary function for dealing with invalid (not supported) exceptions.
void show_invalid_entry_msg (int type, unsigned long esr, unsigned long address) {
    printf("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr, address);
}
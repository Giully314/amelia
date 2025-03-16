// src/peripherals/irq.c
#include <amelia/peripherals/irq.h>
#include <amelia/utils.h>
#include <amelia/printf.h>
#include <amelia/peripherals/system_timer.h>

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
}

// Handle IRQ.
void irq_handle() {
    // For handling multiple interrupts in the same call,
    // wrap this in a loop.
    // Also the mechanism is not precise, because we need to
    // extract each bit with an AND to check.
    unsigned int irq = get32(IRQ_PENDING_REG1);
    switch (irq) {
        case (IRQ_SYSTEM_TIMER_1):
            timer_handle_irq();
            break;
        default:
            printf("Unkwown pending irq: %x\r\n", irq);
    }
}

// Temporary function for dealing with invalid (not supported) exceptions.
void show_invalid_entry_msg (int type, unsigned long esr, unsigned long address) {
    printf("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr, address);
}
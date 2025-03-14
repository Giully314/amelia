// src/kernel/start.c
// DESCRIPTION: This file has methods for the start of the kernel.

#include <amelia/peripherals/uart/mini_uart.h>
#include <amelia/printf.h>
#include <amelia/utils.h>
#include <amelia/peripherals/timer.h>
#include <amelia/peripherals/irq.h>
#include <amelia/hardware/exception_entry.h>

void putc(void *p, char c) { 
    mini_uart_send(c);
}

// Initialize all the resources. This function is executed at EL1.
void kernel_init(unsigned int processor_id) {
    mini_uart_init();
    init_printf(0, putc);
    irq_init_vector_table();
    timer_init();
    irq_enable_interrupt_controller();
    irq_enable();
    
    char id = processor_id + '0'; 
    printf("Kernel init from processor %c with current EL %u\n", id, get_el());
}

// Kernel main, executed at EL1.
void kernel_main(unsigned int processor_id) {
    char id = processor_id + '0'; 
    printf("Kernel main from processor %c with current EL %u\n", id, get_el());

    while (1) {

    }
}
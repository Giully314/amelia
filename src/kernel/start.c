// src/kernel/start.c
// DESCRIPTION: This file has methods for the start of the kernel.

#include <amelia/peripherals/uart/mini_uart.h>
#include <amelia/printf.h>
#include <amelia/utils.h>

void putc(void *p, char c) { 
    mini_uart_send(c);
}

// Function executed by the master process.
void kernel_main(unsigned int processor_id) {
    if (processor_id == 0) {
        init_printf(0, putc);
        mini_uart_init();
    }
    char id = processor_id + '0'; // convert to ascii representation.
    
    printf("Hello from processor %c with current EL %u\n", id, get_el());
    
    if (processor_id == 0) {
        while (1) {
    
        }
    }
}
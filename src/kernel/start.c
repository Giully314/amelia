// src/kernel/start.c
// DESCRIPTION: This file has methods for the start of the kernel.

// #include <amelia/peripherals/uart/mini_uart.h>
#include <amelia/peripherals/uart/pl011_uart.h>

static volatile int semaphore = 0;

// Function executed by the master process.
void kernel_main(unsigned int processor_id) {
    if (processor_id == 0) {
        uart_init();
    }
    char id = processor_id + '0'; // convert to ascii representation.
    
    // Wait for the turn to print.
    while (processor_id != semaphore);
    
    uart_send_string("hello world from ");
    uart_send(id);
    uart_send_string("\r\n");

    // this should be an atomic instruction.n
    ++semaphore;
    
    if (processor_id == 0) {
        while (1) {
    
        }
    }
    // uart_init();
    // uart_send_string("hello world\n");
    // while (1) {
    //     uart_send(uart_recv());
    // }
}

// This function is used 
void print_hello() {

}
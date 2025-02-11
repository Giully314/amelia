// src/kernel/start.c
// DESCRIPTION: This file has methods for the start of the kernel.

#include <amelia/peripherals/uart/mini_uart.h>

void kernel_main() {
    uart_init();
    
    uart_send_string("hello world");

    while (1) {
        uart_send(uart_recv());
    }
}
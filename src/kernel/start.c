// src/kernel/start.c
// DESCRIPTION: This file has methods for the start of the kernel.

#include <amelia/peripherals/uart/mini_uart.h>

void kernel_main() {
    mini_uart_init();
    
    mini_uart_send_string("hello world\r\n");

    while (1) {
        mini_uart_send(uart_recv());
    }
}

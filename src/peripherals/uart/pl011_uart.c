// src/peripherals/uart/pl011_uart.c
#include <amelia/peripherals/uart/pl011_uart.h>
#include <amelia/peripherals/gpio.h>
#include <amelia/utils.h>

void uart_init() {
    unsigned int selector;

    // This set the gpio14 to alternate function 5 txd1 (transimit data) and gpio15
    // to alternate function 5 rxd (read data).
    // The GPFSEL1 register controls the functionalities of the pins 10-19.
    // See page 102 of the board manual.
    selector = get32(GPFSEL1); 
    selector &= ~(7 << 12); // clean gpio 14
    selector |= 2 << 12; // set alt5 for gpio 14
    selector &= ~(7 << 15); // clean gpio15
    selector |= 2 << 15; // set alt5 for gpio 15
    put32(GPFSEL1, selector);

    // This set the gpio to neither pull-up/pull-down.
    // Page 101 of the manual. 
    put32(GPPUD, 0);
    delay(150);
    put32(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);
    put32(GPPUDCLK0, 0);


    // PL011 uart initialization sequence (see CR register synopsis).
    put32(UART_CR_REG, 0);

    // Clear interrupt register.
    put32(UART_ICR_REG, 0);

    // Set baud rate to 115200.
    put32(UART_IBRD_REG, 2);
    put32(UART_FBRD_REG, 0xb);

    // Set 8bits as word length (bit 5,6) and enable FIFO.
    put32(UART_LCRH_REG, 0x7 << 4);

    // Enable Rx, Tx, uart (bit 9, 8, 0).
    put32(UART_CR_REG, 0x301);
}


void uart_send(char c) {
    while (get32(UART_FR_REG) & 0x20);
    put32(UART_DR_REG, c);
}

char uart_recv() {
    while (get32(UART_FR_REG) & 0x10);
    return get32(UART_DR_REG);
}

void uart_send_string(const char* msg) {
    for (int i = 0; msg[i] != '\0'; ++i) {
        uart_send(msg[i]);
    }
}
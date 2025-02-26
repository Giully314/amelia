// src/hardware/mini_uart.c
#include<amelia/peripherals/uart/mini_uart.h>
#include <amelia/peripherals/gpio.h>
#include <amelia/peripherals/aux.h>
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

    // Initialize mini UART.
    put32(AUX_ENABLES, 1); // Enable mini uart (enable register access).
    put32(AUX_MU_CNTL_REG, 0); // Disable auto cflow control and disable receiver and transmitter for initialization.
    put32(AUX_MU_IER_REG, 0); // Disable receive and transmit interrupts (temporary).
    put32(AUX_MU_LCR_REG, 3); // Enable 8 bit mode.
    put32(AUX_MU_MCR_REG, 0); // Set RTS line to be always high.
    put32(AUX_MU_BAUD_REG, 270); // Set baud rate (symbol rate for communication channel) to 115200.
    put32(AUX_MU_CNTL_REG, 3); // Enable transmitter and receiver.
}

void uart_send(char c) {
    // This check if the bit 5 of the data status reg is set, so it can
    // accept atleast one byte to be sent.
    while (!(get32(AUX_MU_LSR_REG) & 0x20));
    put32(AUX_MU_IO_REG, c);
}

char uart_recv() {
    // This check if the first bit of the data status reg is set, so it means
    // that the FIFO buffer has at least one byte that can be read. 
    while (!(get32(AUX_MU_LSR_REG) & 0x01));
    // Note that the data to be read are in the 8 bits of the register.
    return (char)(get32(AUX_MU_IO_REG) & 0xff);
}

void uart_send_string(const char* msg) {
    for (int i = 0; msg[i] != '\0'; ++i) {
        uart_send(msg[i]);
    }
}
// amelia/peripherals/uart/mini_uart.h
// PURPOSE: Implement basics for mini UART (universal async receiver-transmitter).
//
// DESCRIPTION:
//  The Universal Asynchoronous Receiver-Transmitter is protocol for devices which
//  uses async communication.
//  https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter
//  The mini UART implementation has smaller FIFO, no control flow and it is more prone to lose 
//  data at higher baudrate with respect to the PL011 (UART).
//
#ifndef _AMELIA_PERIPHERALS_MINI_UART_H
#define _AMELIA_PERIPHERALS_MINI_UART_H

// Initialize UART section.
void mini_uart_init();


// Send a byte.
void mini_uart_send(char c);

// Receive a byte.
char mini_uart_recv();

// Send a string.
// Precondition: the string must be null terminated.
void mini_uart_send_string(const char* msg);

#endif  // _AMELIA_PERIPHERALS_MINI_UART_H

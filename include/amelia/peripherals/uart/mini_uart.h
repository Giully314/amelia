// amelia/peripherals/uart/mini_uart.h
// PURPOSE: Implement basics for UART (universal async receiver-transmitter).
//
// STRUCTS:
//
// DESCRIPTION:
//  The Universal Asynchoronous Receiver-Transmitter is protocol for devices which
//  uses async communication.
//  https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter
//
#ifndef _AMELIA_HARDWARE_MINI_UART_H
#define _AMELIA_HARDWARE_MINI_UART_H

// Initialize UART section.
void uart_init();


// Send a byte.
void uart_send(char c);

// Receive a byte.
char uart_recv();

void uart_send_string(const char* msg);

#endif  // _AMELIA_HARDWARE_MINI_UART_H

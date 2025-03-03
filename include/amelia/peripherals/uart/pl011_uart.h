// amelia/peripherals/uart/pl011_uart.h
// PURPOSE: Implementation of PL011 UART.
//
// DESCRIPTION:
//

#ifndef _AMELIA_PERIPHERALS_PL011_UART_H
#define _AMELIA_PERIPHERALS_PL011_UART_H

#include <amelia/peripherals/peripherals_base.h>

#define UART_BASE_REG (PERIPHERALS_MEMORY_START + 0x00201000)

// Data register. (32 bit size) The least significant (starting at UART_DR) byte is for the 
// data read and write.
#define UART_DR_REG (UART_BASE_REG + 0x0)
#define UART_RSRECR_REG (UART_BASE_REG + 0x4)
#define UART_FR_REG (UART_BASE_REG + 0x18)
#define UART_IBRD_REG (UART_BASE_REG + 0x24)
#define UART_FBRD_REG (UART_BASE_REG + 0x28)
#define UART_LCRH_REG (UART_BASE_REG + 0x2c)
#define UART_CR_REG (UART_BASE_REG + 0X30)
#define UART_IFLS_REG (UART_BASE_REG + 0x34)
#define UART_IMSC_REG (UART_BASE_REG + 0x38)
#define UART_RIS_REG (UART_BASE_REG + 0x3c)
#define UART_MIS_REG (UART_BASE_REG + 0x40)
#define UART_ICR_REG (UART_BASE_REG + 0x44)
#define UART_DMACR_REG (UART_BASE_REG + 0x48)
#define UART_ITCR_REG (UART_BASE_REG + 080)
#define UART_ITIP_REG (UART_BASE_REG + 0x84)
#define UART_ITOP_REG (UART_BASE_REG + 0x88)
#define UART_TDR_REG (UART_BASE_REG + 0x8c)



// Init PL011 UART.
void uart_init();

// Send a byte using UART.
void uart_send(char c);

// Receive a byte using UART.
char uart_recv();

// Send a string. The string must be null terminated.
void uart_send_string(const char* msg);


#endif // _AMELIA_PERIPHERALS_PL011_UART_H 
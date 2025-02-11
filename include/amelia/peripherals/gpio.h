// amelia/peripherals/gpio.h
// PURPOSE: define general purpose input output (gpio) memory address.
//
// DESCRIPTION:
//
#ifndef _AMELIA_PERIPHERALS_GPIO_H
#define _AMELIA_PERIPHERALS_GPIO_H

#include <amelia/peripherals/peripherals_base.h>

// Register for alternate function for pins from 10-19.
#define GPFSEL1 (PERIPHERALS_MEMORY_START + 0x00200004)

#define GPUUD (PERIPHERALS_MEMORY_START + 0x00200094)

#define GPPUDCLK0 (PERIPHERALS_MEMORY_START + 0x00200098)

#define AUX_ENABLES (PERIPHERALS_MEMORY_START + 0x00215004)

#define AUX_MU_CNTL_REG (PERIPHERALS_MEMORY_START + 0x00215060)

#define AUX_MU_IER_REG (PERIPHERALS_MEMORY_START + 0x00215044)

#define AUX_MU_LCR_REG (PERIPHERALS_MEMORY_START + 0x0021504c)

#define AUX_MU_MCR_REG (PERIPHERALS_MEMORY_START + 0x00215050)

// Register user for setting baud rate.
#define AUX_MU_BAUD_REG (PERIPHERALS_MEMORY_START + 0x00215068)

#define AUX_MU_CNTL_REG (PERIPHERALS_MEMORY_START + 0x00215060)

// Register for read/write data from UART FIFo.
#define AUX_MU_IO_REG (PERIPHERALS_MEMORY_START + 0x00215040)

// Register data status.
#define AUX_MU_LSR_REG (PERIPHERALS_MEMORY_START + 0x00215054)

#endif  // _AMELIA_PERIPHERALS_GPIO_H

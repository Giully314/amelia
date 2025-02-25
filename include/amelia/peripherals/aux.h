// amelia/peripherals/aux.h
// PURPOSE: Define peripherals auxiliary register memory addresses.
//
// DESCRIPTION:
//  These registers are shared between the 3 auxialiary peripherals devices:
//  one mini UART and 2 SPI masters.

#ifndef _AMELIA_PERIPHERALS_AUX_H
#define _AMELIA_PERIPHERALS_AUX_H

#include <amelia/peripherals/peripherals_base.h>

#define AUX_ENABLES (PERIPHERALS_MEMORY_START + 0x00215004)
// Register for read/write data from UART FIFo.
#define AUX_MU_IO_REG (PERIPHERALS_MEMORY_START + 0x00215040)
#define AUX_MU_IER_REG (PERIPHERALS_MEMORY_START + 0x00215044)
#define AUX_MU_LCR_REG (PERIPHERALS_MEMORY_START + 0x0021504c)
#define AUX_MU_MCR_REG (PERIPHERALS_MEMORY_START + 0x00215050)
// Register data status.
#define AUX_MU_LSR_REG (PERIPHERALS_MEMORY_START + 0x00215054)
#define AUX_MU_CNTL_REG (PERIPHERALS_MEMORY_START + 0x00215060)
// Register user for setting baud rate.
#define AUX_MU_BAUD_REG (PERIPHERALS_MEMORY_START + 0x00215068)

#endif

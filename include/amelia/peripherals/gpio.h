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

#define GPPUD (PERIPHERALS_MEMORY_START + 0x00200094)
#define GPPUDCLK0 (PERIPHERALS_MEMORY_START + 0x00200098)
#endif  // _AMELIA_PERIPHERALS_GPIO_H

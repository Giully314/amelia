// amelia/peripherals/gpio.hpp
// PURPOSE: define general purpose input output (gpio) memory address.
//
// DESCRIPTION:
//
#pragma once

#include <amelia/hardware/memory_config.hpp>

// Register for alternate function for pins from 10-19.
#define GPFSEL1 (PERIPHERALS_MEMORY_START + 0x00200004)

#define GPPUD (PERIPHERALS_MEMORY_START + 0x00200094)
#define GPPUDCLK0 (PERIPHERALS_MEMORY_START + 0x00200098)

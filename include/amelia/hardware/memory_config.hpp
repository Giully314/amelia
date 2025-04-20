// amelia/hardware/memory_config.hpp
// PURPOSE: Define physical memory regions addresses.
//
// DESCRIPTION:
//  This file describes the physical memory addresses of the board, defined in the manual.
//

#pragma once

// section 1.2.3
#define PERIPHERALS_MEMORY_START 0x3f000000

// section 7.5
// In the section the base address is reported as 0x7e00b000
// but we use 3f for the arguments discussed in 1.2.3
#define PERIPHERALS_IRQ_START 0x3f00b000

// section 12 of the board manual.
#define PERIPHERALS_SYSTEM_TIMER_START 0x3f003000

// Memory base for the local irq.
#define LOCAL_IRQ_START 0x40000000
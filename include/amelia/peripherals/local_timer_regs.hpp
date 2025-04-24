// amelia/peripherals/local_timer_regs.hpp
// PURPOSE: Define registers and values for the ARM timer.
//
// DESCRIPTION:
//  The registers defined are only for core 0.
//  More information here: https://datasheets.raspberrypi.com/bcm2836/bcm2836-peripherals.pdf
//
#pragma once

#include <amelia/hardware/memory_config.hpp>

#define LOCAL_TIMER_CONTROL_STATUS (LOCAL_IRQ_START + 0x34)

#define LOCAL_TIMER_IRQ_CLEAR_RELOAD (LOCAL_IRQ_START + 0x38)

#define LOCAL_TIMER_INTERRUPT_ENABLE (1 << 29)
#define LOCAL_TIMER_ENABLE (1 << 28)

#define LOCAL_TIMER_INTERRUPT_CLEAR (1 << 31)

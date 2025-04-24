// amelia/peripherals/local_timer.hpp
// PURPOSE: Define the ARM (local) timer.
//
// STRUCTS:
//  LocalTimer: Control class for handling the arm local timer for a single core.
//
// DESCRIPTION:
//  The local timer differs from the system timer in different ways;
//  the system timer is a global timer used as a reference clock for the events
//  in the system while the local timer is used only by the core itself
//  and for communication purposes between the cores.
//  More information https://datasheets.raspberrypi.com/bcm2836/bcm2836-peripherals.pdf
//
#pragma once

#include <amelia/types.hpp>

namespace amelia {

struct LocalTimer {
    static auto init() -> void;

    // The interval must be contained in 28 bits.
    static auto set_interval(const u32 interval) -> void;

    static auto enable() -> void;

    static auto disable() -> void;

    static auto handle_irq() -> void;
};

} // namespace amelia

// Initialize local timer.
void local_timer_init();

// Enable local timer.
void local_timer_enable_irq();

// Disable local timer;
void local_timer_disable_irq();

// Interrupt handler for local timer.
void local_timer_handle_irq();

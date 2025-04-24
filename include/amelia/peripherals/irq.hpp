// amelia/peripherals/irq.hpp
// PURPOSE: Define API for interrupts.
//
// DESCRIPTION:
//  For now we work only with IRQ, that's why in irq.S we set 2 as a value for
//  the DAIF register.
//  D (bit 9): debug exception masked if set to 1.
//  A (bit 8): SError exception masked if set to 1.
//  I (bit 7): IRQ exception masked if set to 1.
//  F (bit 6): FIQ exception masked if set to 1.
//  Using daifclr and daifset we can clear/set directly the bits using values
//  for the first 4 bits. Set is used for masking the exceptions.
//  Masking an interrupt means that the interrupt is ignored by the CPU.
//
#pragma once

#include <amelia/types.hpp>

extern "C" {

auto irq_enable() -> void;

auto irq_disable() -> void;

} // extern "C"

namespace amelia {

struct IRQController {
    // Enable a specific irq.
    // irq_to_enable specifies for each bit (check manual) a specific
    // peripheral wired to the controller that can be masked or unmasked.
    static auto enable(u32 irq_to_enable) -> void;

    // Enable all irq.
    static auto enable_all_devices() -> void;

    // Masking irq means to temporary ignore notifications
    // from interrupts.
    static auto mask() -> void;

    // Unmasking irq means to not ignore the interrupts.
    static auto unmask() -> void;
};

} // namespace amelia

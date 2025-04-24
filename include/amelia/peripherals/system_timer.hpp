// amelia/peripherals/system_timer.hpp
// PURPOSE: Define system timer class.
//
// DESCRIPTION:
//  The system timer is described in the section 12 of the board manual.
//  It can be seen as the "global" timer, opposite to the local timer that
//  each arm core have. It can handle up to 4 different interval for irq.
//
// TODO:
//  Support for setting 4 different irq for different intervals.

#pragma once

#include <amelia/types.hpp>

namespace amelia {

struct SystemTimer {
    static auto init() -> void;

    static auto set_interval(u32 interval) -> void;

    static auto handle_irq() -> void;
};

} // namespace amelia

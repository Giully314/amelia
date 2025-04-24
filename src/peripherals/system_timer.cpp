// src/peripherals/system_timer.cpp

// clang-format off
#include <amelia/peripherals/system_timer.hpp>
// clang-format on

#include <amelia/hardware/hardware_utils.hpp>
#include <amelia/peripherals/system_timer_regs.hpp>
#include <amelia/printf.hpp>

namespace amelia {

static u32 current_interval = 500000;
static u32 current_value = 0;

auto SystemTimer::init() -> void {
    current_value = mem_read32(SYSTEM_TIMER_CLO);
    current_value += current_interval;
    mem_write32(SYSTEM_TIMER_C1, current_value);
}

auto SystemTimer::set_interval(u32 interval) -> void {
    current_value = mem_read32(SYSTEM_TIMER_CLO);
    current_interval = interval;
    current_value += interval;
    mem_write32(SYSTEM_TIMER_C1, current_value);
}

auto SystemTimer::handle_irq() -> void {
    current_value += current_interval;
    mem_write32(SYSTEM_TIMER_C1, current_value);
    // Clear the bit of irq.
    mem_write32(SYSTEM_TIMER_CS, SYSTEM_TIMER_CS_M1);
    printf("Timer interrupt received\r\n");
}

} // namespace amelia

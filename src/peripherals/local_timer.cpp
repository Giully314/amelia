// src/peripherals/local_timer.cpp

#include <amelia/peripherals/local_timer.hpp>

#include <amelia/hardware/hardware_utils.hpp>
#include <amelia/peripherals/local_timer_regs.hpp>
#include <amelia/printf.hpp>

namespace amelia {

static u32 current_interval = 0;

auto LocalTimer::init() -> void {
    LocalTimer::set_interval(200000);
}

auto LocalTimer::set_interval(const u32 interval) -> void {
    current_interval = interval;
    mem_set32(LOCAL_TIMER_CONTROL_STATUS, current_interval);
}

auto LocalTimer::enable() -> void {
    u32 setup = LOCAL_TIMER_INTERRUPT_ENABLE | LOCAL_TIMER_ENABLE;
    mem_set32(LOCAL_TIMER_CONTROL_STATUS, setup);
}

auto LocalTimer::disable() -> void {
    u32 setup = LOCAL_TIMER_INTERRUPT_ENABLE | LOCAL_TIMER_ENABLE;
    mem_clear32(LOCAL_TIMER_CONTROL_STATUS, setup);
}

auto LocalTimer::handle_irq() -> void {
    mem_write32(LOCAL_TIMER_IRQ_CLEAR_RELOAD, LOCAL_TIMER_INTERRUPT_CLEAR);
    printf("Local timer interrupt.\r\n");
}

} // namespace amelia

// src/peripherals/irq.cpp

#include <amelia/peripherals/irq.hpp>

#include <amelia/hardware/hardware_utils.hpp>
#include <amelia/peripherals/irq_regs.hpp>
#include <amelia/peripherals/system_timer.hpp>
#include <amelia/printf.hpp>

static const char *entry_error_messages[] = {
    "SYNC_INVALID_EL1t", "IRQ_INVALID_EL1t",
    "FIQ_INVALID_EL1t", "ERROR_INVALID_EL1T",

    "SYNC_INVALID_EL1h", "IRQ_INVALID_EL1h",
    "FIQ_INVALID_EL1h", "ERROR_INVALID_EL1h",

    "SYNC_INVALID_EL0_64", "IRQ_INVALID_EL0_64",
    "FIQ_INVALID_EL0_64", "ERROR_INVALID_EL0_64",

    "SYNC_INVALID_EL0_32", "IRQ_INVALID_EL0_32",
    "FIQ_INVALID_EL0_32", "ERROR_INVALID_EL0_32"};

extern "C" {
// Temporary function for dealing with invalid (not supported) exceptions.
auto show_invalid_entry_msg(amelia::i32 type, amelia::u64 esr, amelia::u64 address) -> void {
    printf("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr,
           address);
}

// This function is called by the exception entry control flow in entry.S.
// It is the entry point for irq handling.
auto irq_handle() -> void {
    amelia::u32 irq = mem_read32(IRQ_PENDING_REG1);
    if(irq & IRQ_SYSTEM_TIMER_1) {
        amelia::SystemTimer::handle_irq();
        irq &= ~IRQ_SYSTEM_TIMER_1;
    }
    if(irq != 0) {
        printf("Unkwown base pending irq: %x\r\n", irq);
    }
}
} // extern "C"

namespace amelia {

auto IRQController::enable(u32 irq_to_enable) -> void {
    mem_write32(IRQ_ENABLE_REG1, irq_to_enable);
}

auto IRQController::enable_all_devices() -> void {
    // Enable irq for system timer and mini uart.
    u32 irq_to_enable = IRQ_SYSTEM_TIMER_1 | IRQ_AUX;
    IRQController::enable(irq_to_enable);
}

auto IRQController::mask() -> void {
    irq_disable();
}

auto IRQController::unmask() -> void {
    irq_enable();
}

} // namespace amelia

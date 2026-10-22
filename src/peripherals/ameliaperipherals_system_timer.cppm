// src/peripherals/ameliaperipherals_system_timer.cppm
// PURPOSE:
// DESCRIPTION:
// USAGE:
//  This resource should be initialized once (in the BSS section for example).


export module amelia.peripherals.system_timer;

import amelia.types;
import amelia.peripherals.regs;
import amelia.print.printf;


namespace amelia {
namespace peripherals {

struct TimerRegisters {
    volatile u32 cs;            // control status.
    volatile u32 clo;           // counter lower 32 bits.
    volatile u32 chi;           // counter higher 32 bits.
    volatile u32 compare[4];    // compare registers.
};

export struct SystemTimer {
    static auto init() -> void {
        current = regs->clo;
        current += interval;
        regs->compare[0] = current;
    }

    // auto reset() -> void;

    static auto handler() -> void {
        current += interval;
        regs->compare[1] = current;
        regs->cs = 1;
        tfp_printf("hello from timer interrupt\n");
    }


private:
    inline static TimerRegisters* regs = reinterpret_cast<TimerRegisters*>(base + 0x00003000);
    inline static constexpr u32 interval = 200'000;
    inline static u32 current{0};
};

} // namespace peripherals
} // namespace amelia
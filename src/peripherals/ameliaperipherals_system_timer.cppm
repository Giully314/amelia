// src/peripherals/ameliaperipherals_system_timer.cppm
// PURPOSE:
// DESCRIPTION:
// USAGE:
//  This resource should be initialized once (in the BSS section for example).


export module amelia.peripherals.system_timer;

import amelia.types;
import amelia.peripherals.regs;


namespace amelia {
namespace peripherals {

struct TimerRegisters {
    u32 cs;            // control status.
    u32 clo;           // counter lower 32 bits.
    u32 chi;           // counter higher 32 bits.
    u32 compare[4];    // compare registers.
};

export struct SystemTimer {
    static auto init() -> void {
        current = regs->clo;
        current += interval;
        regs->compare[3] = current;
    }

    // auto reset() -> void;


private:
    inline static TimerRegisters* regs = reinterpret_cast<TimerRegisters*>(base + 0x00003000);
    inline static constexpr u32 interval = 200'000;
    inline static u32 current{0};
};

} // namespace peripherals
} // namespace amelia
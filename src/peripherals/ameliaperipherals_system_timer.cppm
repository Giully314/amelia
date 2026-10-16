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

struct SystemTimer {
    inline static constexpr ptr_t b = base + 0x00003000;    // System timer base address.
    inline static constexpr ptr_t cs = b + 0x00;            // control status.
    inline static constexpr ptr_t clo = b + 0x04;           // counter lower 32 bits.
    inline static constexpr ptr_t chi = b + 0x08;           // counter higher 32 bits.
    inline static constexpr ptr_t c0 = b + 0x0c;            // compare 0.
    inline static constexpr ptr_t c1 = b + 0x10;            // compare 1.
    inline static constexpr ptr_t c2 = b + 0x14;            // compare 2.
    inline static constexpr ptr_t c3 = b + 0x18;            // compare 3.


    SystemTimer() {

    }

    auto reset() -> void;


private:
};

} // namespace peripherals
} // namespace amelia
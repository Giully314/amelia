// src/peripherals/ameliaperipherals_regs.cppm
// PURPOSE:
// DESCRIPTION:

export module amelia.peripherals.regs;

import amelia.types;

#define AMELIA_LOW_PERIPHERAL_MODE

export namespace amelia {
export namespace peripherals {
    // See section 1.2.4 of the board manual. 
    #ifdef AMELIA_LOW_PERIPHERAL_MODE
    inline constexpr ptr_t base = 0xfe000000;
    #else
    inline constexpr ptr_t base = 0x07e000000;
    #endif
} // namespace peripherals
} // namespace amelia

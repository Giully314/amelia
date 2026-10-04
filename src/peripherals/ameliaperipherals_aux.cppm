// src/peripherals/ameliaperipherals_aux.cppm
// PURPOSE: Define peripherals auxiliary memory registers.  
// DESCRIPTION:

export module amelia.peripherals.aux;

import amelia.types;
import amelia.peripherals.regs;

namespace amelia {

// Define register addresses for the auxiliary peripherals. 
namespace aux {    
    inline constexpr ptr_t base = low_peripherals_address + 0x00215000;
    inline constexpr ptr_t irq = base + 0x00;
    inline constexpr ptr_t enables = base + 0x04;
    inline constexpr ptr_t mu_io_reg = base + 0x40;


} // namespace aux
} // namespace amelia
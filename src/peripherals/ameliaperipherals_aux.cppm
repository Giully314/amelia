// src/peripherals/ameliaperipherals_aux.cppm
// PURPOSE: Define peripherals auxiliary memory registers.  
// DESCRIPTION: 
//  Section 2.1 of the manual.

export module amelia.peripherals.aux;

import amelia.types;
import amelia.peripherals.regs;

namespace amelia {
namespace aux {    
    /// Define register addresses for the auxiliary peripherals. 
    export struct Register {
        inline static constexpr ptr_t base = peripherals::base + 0x00215000;
        inline static constexpr ptr_t irq = base + 0x00;
        inline static constexpr ptr_t enables = base + 0x04;
        inline static constexpr ptr_t mu_io_reg = base + 0x40;
        inline static constexpr ptr_t mu_ier_reg = base + 0x44;
        inline static constexpr ptr_t mu_iir_reg = base + 0x48;
        inline static constexpr ptr_t mu_lcr_reg = base + 0x4c;
        inline static constexpr ptr_t mu_mcr_reg = base + 0x50;
        inline static constexpr ptr_t mu_lsr_reg = base + 0x54;
        inline static constexpr ptr_t mu_cntl_reg = base + 0x60;
        inline static constexpr ptr_t mu_baud_reg = base + 0x68;
        inline static constexpr ptr_t mu__reg = base + 0x68;
    };

} // namespace aux
} // namespace amelia
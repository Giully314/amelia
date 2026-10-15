// src/exceptions/ameliaexceptions_gic.cppm
// PURPOSE:
// CLASSES:
// DESCRIPTION:


export module amelia.exceptions.gic;

import amelia.exceptions.gic_regs;
import amelia.types;

namespace amelia {
namespace exceptions {

class GIC {
public:
    GIC(ptr_t gicd_base, ptr_t gicc_base) : 
        gicd_(reinterpret_cast<GICDRegisters*>(gicd_base)), gicc_(reinterpret_cast<GICCRegisters*>(gicc_base)) {}

    auto enable_irq() -> void;
    auto disable_irq() -> void;



    auto enable() -> void {
        
    }

    auto disable() -> void {

    }

private:
    GICDRegisters* gicd_;
    GICCRegisters* gicc_;
};

} // namespace exceptions
} // namespace amelia
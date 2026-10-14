// src/exceptions/ameliaexceptions_gic_regs.cppm
// PURPOSE:
// DESCRIPION:


export module amelia.exceptions.gic_regs;

import amelia.types;

namespace amelia {
namespace exceptions {

// Defined in the gic architecture specification file v2. To the right the offsets are defined.
struct GICDRegisters {
    volatile u32 ctlr;                  // 0x0000   rw
    volatile u32 typer;                 // 0x0004   ro 
    volatile u32 iidr;                  // 0x0008   ro
    volatile u32 reserved0[29];         // 0x000C
    volatile u32 igroupr[32];           // 0x0080   rw   1 bit per interrupt
    volatile u32 isenabler[32];         // 0x0100   rw   
    volatile u32 icenabler[32];         // 0x0180   rw   
    volatile u32 ispendr[32];           // 0x0200   rw   
    volatile u32 icpendr[32];           // 0x0280   rw   
    volatile u32 isactiver[32];         // 0x0300   rw   
    volatile u32 icactiver[32];         // 0x0380   rw   
    volatile u32 ipriorityr[255];       // 0x0400   ro for the first, rw for the others
    volatile u32 reserved1;             // 0x07FC   
    volatile u32 itargetsr[255];        // 0x0800   ro for the first, rw for the others
    volatile u32 reserved2;             // 0x0BFC
    volatile u32 icfgr[64];             // 0x0C00   rw
    volatile u32 reserved3[64];         // 0x0D00
    volatile u32 nsacr[64];             // 0x0E00   rw
    volatile u32 sgir;                  // 0x0F00   wo
    volatile u32 reserved4[3];          // 0x0F04 
    volatile u32 cpendsgir[4];          // 0x0F10   rw
    volatile u32 spendsgir[4];          // 0x0F20   rw
    volatile u32 reserved5[52];         // 0x0F30
};


struct GICCRegisters {
    
};


} // namespace exceptions
} // namespace amelia
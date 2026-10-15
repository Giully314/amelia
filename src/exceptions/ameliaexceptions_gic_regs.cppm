// src/exceptions/ameliaexceptions_gic_regs.cppm
// PURPOSE: Define generic interrupt controller registers.
// CLASSES:
//  GICDRegisters: GIC distributor registers.
//  GICCRegisters: GIC CPU interface registers.
//  
// DESCRIPION:
//  
// RESOURCES:
//  ARM GIC v2 architecture specs.


export module amelia.exceptions.gic_regs;

import amelia.types;

namespace amelia {
export namespace exceptions {

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
    volatile u8 ipriorityr[1020];       // 0x0400   ro for the first, rw for the others
    volatile u32 reserved1;             // 0x07FC   
    volatile u8 itargetsr[1020];        // 0x0800   ro for the first, rw for the others
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
    volatile u32 ctlr;          // 0x000  rw  CPU interface control
    volatile u32 pmr;           // 0x004  rw  priority mask
    volatile u32 bpr;           // 0x008  rw  binary point
    volatile u32 iar;           // 0x00C  ro  interrupt acknowledge
    volatile u32 eoir;          // 0x010  wo  end of interrupt
    volatile u32 rpr;           // 0x014  ro  running priority
    volatile u32 hppir;         // 0x018  ro  highest priority pending
    volatile u32 abpr;          // 0x01C  rw  aliased binary point
    volatile u32 aiar;          // 0x020  ro  aliased IAR (secure only)
    volatile u32 aeoir;         // 0x024  wo  aliased EOIR (secure only)
    volatile u32 ahppir;        // 0x028  ro  aliased HPPIR (secure only)
    volatile u32 reserved0[5];  // 0x02C - 0x03F
    volatile u32 impdef[36];    // 0x040 - 0x0CF  implementation defined
    volatile u32 apr[4];        // 0x0D0  rw  active priorities
    volatile u32 nsapr[4];      // 0x0E0  rw  non-secure active priorities
    volatile u32 reserved1[3];  // 0x0F0 - 0x0FB
    volatile u32 iidr;          // 0x0FC  ro  CPU interface identification
    volatile u32 reserved2[960];// 0x100 - 0xFFF
    volatile u32 dir;           // 0x1000 wo  deactivate interrupt
};


} // namespace exceptions
} // namespace amelia
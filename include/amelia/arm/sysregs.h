// amelia/arm/sysregs.h
// PURPOSE: Define ARM system register configuration values.
//

#ifndef _AMELIA_ARM_SYSREGS_H
#define _AMELIA_ARM_SYSREGS_H

// ***********************
// System Control Register Exception Level 1 (SCTLR_EL1), Page 2654 of AArch64 reference manual.
// ***********************

#define SCTLR_EL1_MMU_DISABLED (0 << 0)
#define SCTLR_EL1_MMU_ENABLED (1 << 0)

// Disable cache for data.
#define SCTLR_EL1_D_CACHE_DISABLED (0 << 2)

// Disable cache for instruction.
#define SCTLR_EL1_I_CACHE_DISABLED (0 << 12)

// Set little endian for EL0.
#define SCTLR_EL1_E0E_LITTLE_ENDIAN (0 << 24)

// Set little endian for EL1
#define SCTLR_EL1_EE_LITTLE_ENDIAN (0 << 25)

#define SCTLR_EL1_RESERVED (3 << 28) | (3 << 22) | (1 << 20) | (1 << 11)

#define SCTLR_EL1_VALUE_MMU_DISABLED                               \
	(SCTLR_EL1_RESERVED | SCTLR_EL1_EE_LITTLE_ENDIAN |         \
	 SCTLR_EL1_D_CACHE_DISABLED | SCTLR_EL1_I_CACHE_DISABLED | \
	 SCTLR_EL1_MMU_DISABLED)

// ***********************
// Hypervisor Configuration Register EL2 (hcr_el2), Page 2487 of AArch64 reference manual.
// ***********************

#define HCR_EL2_RW (1 << 31)
#define HCR_EL2_VALUE HCR_EL2_RW

// ***********************
// Secure Configuration Register EL3 (scr_el3), Page 2648 of AArch64 reference manual.
// ***********************

#define SCR_EL3_RESERVED (3 << 4)

// Execution state control flow.
#define SCR_EL3_RW (1 << 10)

// Non secure bit, set to 0 to indicate EL0 and EL1 are in secure state.
#define SCR_EL3_NS (1 << 0)

#define SCR_EL3_VALUE (SCR_EL3_RESERVED | SCR_EL3_RW | SCR_EL3_NS)

// ***********************
// Saved Program Status Register EL2, Page 383 of AArch64 reference manual.
// ***********************

// Disable exceptions.
#define SPSR_EL2_MASK_ALL (7 << 6)

// Use EL1 with its SP.
#define SPSR_EL2_EL1h (5 << 0)

#define SPSR_EL2_VALUE (SPSR_EL2_EL1h | SPSR_EL2_MASK_ALL)

// ***********************
// Saved Program Status Register EL3, Page 389 of AArch64 reference manual.
// ***********************

// Disable exceptions.
#define SPSR_EL3_MASK_ALL (7 << 6)

// Use EL2 with its SP.
#define SPSR_EL3_EL1h (9 << 0)

#define SPSR_EL3_VALUE (SPSR_EL3_EL1h | SPSR_EL3_MASK_ALL)

// ***********************
// CPACR_EL1 controls for SIMD and FP registers, Page 2411 of AArch64 reference manual.
// ***********************

#define CPACR_EL1_FPEN_ENABLED (3 << 20)

#define CPACR_VALUE (CPACR_EL1_FPEN_ENABLED)

// ***********************
// ESR_EL1, Exception syndrom register (EL1). Page 2431 of AArch64 reference manual.
// ***********************

// Check page 2438 for these values.
#define ESR_ELx_EC_SHIFT 26
#define ESR_ELx_EC_SVC64 0x15

// ***********************
// SPSR_EL1, Saved Program Status Register (EL1). Page 377 of AArch64 reference manual.
// ***********************

// Value for the Program status register.
#define PSR_MODE_EL0t 0x00000000
#define PSR_MODE_EL1t 0x00000004
#define PSR_MODE_EL1h 0x00000005
#define PSR_MODE_EL2t 0x00000008
#define PSR_MODE_EL2h 0x00000009
#define PSR_MODE_EL3t 0x0000000c
#define PSR_MODE_EL3h 0x0000000d

#endif // _AMELIA_ARM_SYSREGS_H

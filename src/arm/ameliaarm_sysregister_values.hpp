// src/arm/ameliaarm_register_values.hpp
// PURPOSE: Define values to be set in the arm registers at boot time.
//
// DESCRIPTION:
//  This file is used primarily to be included in the boot process to set values special registers to enable/disable hardware functionalities such as 
//  MMU, cache and so on.
// 
// RESOURCES:
//  armv8 manual: https://support.arm.com/documentation/ddi0487/ca/


#pragma once

// System Control Register (EL1) settings, page 2654.
#define SCTLR_EL1_RESERVED (0b11 << 28) | (0b11 << 22) | (0b1 << 20) | (0b1 << 11)
#define SCTLR_EL1_EE_LITTLE_ENDIAN (0b0 << 25)
#define SCTLR_EL1_E0E_LITTLE_ENDIAN (0b0 << 24)
#define SCTLR_EL1_I_CACHE_DISABLED (0b0 << 12)
#define SCTLR_EL1_D_CACHE_DISABLED (0b0 << 2)
#define SCTLR_EL1_M_MMU_DISABLED (0b0 << 0)
#define SCTLR_EL1_VALUE (SCTLR_EL1_RESERVED | SCTLR_EL1_EE_LITTLE_ENDIAN | SCTLR_EL1_E0E_LITTLE_ENDIAN | SCTLR_EL1_I_CACHE_DISABLED | SCTLR_EL1_D_CACHE_DISABLED | SCTLR_EL1_M_MMU_DISABLED)


// Architectural feature trap register (EL1), page 2414
// The SIMD instructions are used by the compiler with printf.
#define CPTR_EL2_TFP_ENABLE_SIMD (0b0 << 10)
#define CPTR_EL2_VALUE (CPTR_EL2_TFP_ENABLE_SIMD)

// Architectural feature access control register (EL1), page 2411
// The SIMD instructions are used by the compiler with printf.
#define CPACR_EL1_FPEN_ENABLE_SIMD (0b11 << 20)
#define CPACR_EL1_VALUE (CPACR_EL1_FPEN_ENABLE_SIMD)

// Hypervisor configuration register (EL2), page 2487
#define HCR_EL2_RW (0b1 << 31)
// NOTE: cortex a72 doesn't support VHE so setting this bit is useless.
// Set normal os mode. 
// #define HCR_EL2_E2H (0b1 << 34)
#define HCR_EL2_VALUE (HCR_EL2_RW)

// Secure configuration register (EL3), page 2648
#define SCR_EL3_RESERVED (0b11 << 4)
#define SCR_EL3_RW (0b1 << 10)
#define SCR_EL3_NS (0b1 << 0)
#define SCR_EL3_VALUE (SCR_EL3_RESERVED | SCR_EL3_RW | SCR_EL3_NS)

// Saved program status register (EL3), page 389. Hold the saved process state when an exception is taken to EL3.
#define SPSR_EL3_MASK_ALL (0b111 << 6)
// Use the stack pointer setup by the handler (el2h). The 't' version uses the thread stack pointer (user).
#define SPSR_EL3_EL2h (0b1001 << 0)
#define SPSR_EL3_VALUE (SPSR_EL3_MASK_ALL | SPSR_EL3_EL2h)



#define SPSR_EL2_MASK_ALL (0b111 << 6)
#define SPSR_EL2_EL1h (0b0101 << 0)
#define SPSR_EL2_VALUE (SPSR_EL2_MASK_ALL | SPSR_EL2_EL1h)
// src/entry/amliaentry_exception_vector.hpp
// PURPOSE:
// DESCRIPTION:

#pragma once

// Only assembler-safe content (#define) here: this file is included from .S files.


// el1_t: exception is taken from el1 but SP is shared with el0.
#define SYNC_INVALID_EL1t 0
#define IRQ_INVALID_EL1t 1
#define FIQ_INVALID_EL1t 2
#define SERROR_INVALID_EL1t 3

// el1_t: exception is taken from el1 and SP is allocated for el1.
#define SYNC_INVALID_EL1h 4
#define IRQ_INVALID_EL1h 5
#define FIQ_INVALID_EL1h 6
#define SERROR_INVALID_EL1h 7

// el0 64 bit mode.
#define SYNC_INVALID_EL0_64 8
#define IRQ_INVALID_EL0_64 9
#define FIQ_INVALID_EL0_64 10
#define SERROR_INVALID_EL0_64 11

// el0 32 bit mode.
#define SYNC_INVALID_EL0_32 12
#define IRQ_INVALID_EL0_32 13
#define FIQ_INVALID_EL0_32 14
#define SERROR_INVALID_EL0_32 15
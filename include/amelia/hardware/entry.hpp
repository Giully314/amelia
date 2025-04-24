// amelia/hardware/entry.hpp
// PURPOSE: Define information about hardware exceptions.
//
// DESCRIPTION:
//  This file defines types and other informations for everything related to exceptions
//  at hardware level (also known as interruputs in other terminologies).
//  We have 4 types of exceptions:
//  1) Synchronous exception
//  2) IRQ (Interrupt request)
//  3) FIQ (Fast Interrupt request)
//  4) SError (System Error)
//  Only 1) is executed by the processor itself (usually for system calls) and so
//  it is synchronous, while the others are executed by external hardware and
//  can happen at any time in the current control flow. When an exception is raised
//  the processor jump to a location in memory called interrupt vector table.
//  This table has, for each type of exception and for each of the 4 handler,
//  a piece of code to execute to handle that type of exception.
//

#define STACK_FRAME_SIZE 272
#define S_X0 0 // offset of x0 in the stack entry.

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

#define SYNC_ERROR 16
#define SYSCALL_ERROR 17

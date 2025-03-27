// amelia/hardware/cpu.h
// PURPOSE: Define data related to a CPU.
//
// STRUCTS:
//  CPUContext: Save register data for a context switch.
//
// DESCRIPTION:
//
#ifndef _AMELIA_HARDWARE_CPU_H
#define _AMELIA_HARDWARE_CPU_H

#include <amelia/basic_types.h>

// Save the register content for a context switch.
// Because the context switch is done by calling a function, the ARM procedure
// call convention says that it is responsability of the caller to save the other
// registers not mentioned in this struct.
struct CPUContext {
	u64 x19;
	u64 x20;
	u64 x21;
	u64 x22;
	u64 x23;
	u64 x24;
	u64 x25;
	u64 x26;
	u64 x27;
	u64 x28;

	// Floating point registers (64 bit version)
	u64 d8;
	u64 d9;
	u64 d10;
	u64 d11;
	u64 d12;
	u64 d13;
	u64 d14;
	u64 d15;
	
	u64 fp; // x29
	u64 sp; // x9
	u64 pc;
};

#endif // _AMELIA_HARDWARE_CPU_H

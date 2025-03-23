// amelia/utils.h
// PURPOSE: Define utility functions and structures.
//
// DESCRIPTION:
//  This file provides basic utilities to access hardware components.
//

#ifndef _AMELIA_UTILS_H
#define _AMELIA_UTILS_H

#include <amelia/basic_types.h>

// Wait for time specified in cycles.
void delay(u64 time);

// Write 32 bits to a device specified by id.
void put32(u64 id, u32 value);

// Read 32 bits from a device specified by id.
unsigned int get32(u64 id);

// Get the current Expection Level.
u64 get_el();

// Set the bits of a register. This function compute the `or` operation on
// a register with the passed value.
void set32(u64 addr, u32 value);

// Clear bits of a register.
void clear32(u64 addr, u32 value);

#endif // _AMELIA_UTILS_H

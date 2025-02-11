// amelia/utils.h
// PURPOSE: Define utility functions and structures.
//
// DESCRIPTION:
//

#ifndef _AMELIA_UTILS_H
#define _AMELIA_UTILS_H

// Wait for time specified in nanoseconds.
extern void delay(unsigned long time);

// Write 32 bits to a device specified by id.
extern void put32(unsigned long id, unsigned int value);

// Read 32 bits from a device specified by id.
extern unsigned int get32(unsigned long id);

#endif  // _AMELIA_UTILS_H

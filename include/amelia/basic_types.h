// amelia/basic_types.h
// PURPOSE: Define fixed width basic types.
//
// DESCRIPTION:
//

#ifndef _AMELIA_BASIC_TYPES_H
#define _AMELIA_BASIC_TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef u8 byte;

// Holds a memory address.
typedef u64 ptr_t;


#endif // _AMELIA_BASIC_TYPES_H
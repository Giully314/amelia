// amelia/hardware/hardware_utils.hpp
// PURPOSE: Define low level hardware functions.
//
//

#include <amelia/types.hpp>

extern "C" {

// Wait for n nanoseconds.
void delay(amelia::u64 nanoseconds);

// Get value of 4 bytes at address.
amelia::u32 mem_read32(amelia::u64 address);

// Put a value into location specified by address.
void mem_write32(amelia::u64 address, amelia::u32 value);

// Get current exception level.
amelia::u32 get_el();

} // extern C
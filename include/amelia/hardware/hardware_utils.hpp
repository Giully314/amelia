// amelia/hardware/hardware_utils.hpp
// PURPOSE: Define low level hardware functions.
//
//

#include <amelia/types.hpp>

extern "C" {

// Wait for n nanoseconds.
auto delay(amelia::u64 nanoseconds) -> void;

// Get value of 4 bytes at address.
auto mem_read32(amelia::u64 address) -> amelia::u32;

// Put a value into location specified by address.
auto mem_write32(amelia::u64 address, amelia::u32 value) -> void;

// Set to 1 the bits specified by value at the given address.
auto mem_set32(amelia::u64 address, amelia::u32 value) -> void;

// Set to 0 the bits specified by value at the given address.
auto mem_clear32(amelia::u64 address, amelia::u32 value) -> void;

// Get current exception level.
auto get_el() -> amelia::u32;

} // extern C
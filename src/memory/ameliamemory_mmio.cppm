// src/memory/ameliamemory_mmio.cppm
// PURPOSE: Define memory mapped input output functions.
// DESCRIPTION:


export module amelia.memory.mmio;

import amelia.types;
import amelia.utils;


export namespace amelia {

namespace memory {

    /// @brief Read a 32 bit value from an address. 
    /// @param address 
    /// @return 
    auto mmio_read(u64 address) -> u32 {
        return read32(address);
    }

    /// @brief Write a 32 bit value to an address.
    /// @param address 
    /// @param value 
    /// @return 
    auto mmio_write(u64 address, u32 value) -> void {
        write32(address, value);
    }
} // namespace memory
    
} // namespace amelia

// amelia/memory/block.hpp
// PURPOSE: Define a memory block.
//
// CLASSES:
//  MemoryBlock: info about a block of memory returned by allocators.
//

#pragma once

#include <amelia/types.hpp>

namespace amelia {

struct MemoryBlock {
    void *data{nullptr};
    // Size in bytes.
    u64 size{0};
};

} // namespace amelia

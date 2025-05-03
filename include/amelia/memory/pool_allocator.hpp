// amelia/memory/pool_allocator.hpp
// PURPOSE: Define a pool allocator for blocks of fixed memory.
//
// CLASSES:
//  PoolAllocator:
//   Divide a block of memory into chunks of equal size by handling the pool
//   and keep it aligned.
//
// DESCRIPTION:
//

#pragma once

#include <amelia/memory/block.hpp>
#include <amelia/types.hpp>

namespace amelia {

class PoolAllocator {
public:
    PoolAllocator(const MemoryBlock block_, const u64 obj_size_, const u64 alignment_);

    // TODO:
    ~PoolAllocator();

    [[nodiscard]] auto allocate([[maybe_unused]] const u64 = 0) -> MemoryBlock;
    auto deallocate(const MemoryBlock b) -> void;

private:
    MemoryBlock block;
    u64 obj_size{0};
    u64 alignment{0};
    // Used to keep track of available objects in the pool.
    byte* bitmap{nullptr};
    u16 bitmap_size{0};

    // Start of the pool in the memory block.
    byte* pool{nullptr};
    // Number of total objects.
    u32 capacity{0};
};

} // namespace amelia

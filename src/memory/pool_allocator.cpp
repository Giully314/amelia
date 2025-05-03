// src/memory/pool_allocator.cpp
// TODO: implement alignment for objects.

#include <amelia/memory/pool_allocator.hpp>

#include <amelia/algorithms/minmax.hpp>
#include <amelia/memory/memops.hpp>

namespace amelia {

PoolAllocator::PoolAllocator(const MemoryBlock block_, const u64 obj_size_, const u64 alignment_)
    : block{block_}, obj_size{obj_size_}, alignment{alignment_} {
    // Steps:
    // Compute the alignment.
    // Compute the real capacity (including the cost the bitmap).
    // TODO: Adjust the alignment for each object.

    memzero(block.data, block.size);

    bitmap = reinterpret_cast<byte*>(memalign(block.data, alignment));

    u32 c = block.size / obj_size;
    bitmap_size = max<u16>(c / 8, 1);

    pool = reinterpret_cast<byte*>(memalign(bitmap + bitmap_size, alignment));
    capacity = c - (reinterpret_cast<ptr_t>(pool) - reinterpret_cast<ptr_t>(block.data));

    bitmap_size = max<u16>(capacity / 8, 1);
}

auto PoolAllocator::allocate(const u64) -> MemoryBlock {
    for(u32 i = 0; i < bitmap_size; ++i) {
        // Iterate over the 8 bits.
        byte j = 0b10000000;
        u32 idx = 0;
        while(j != (byte)0) {
            if((bitmap[i] & j) == 0) {
                bitmap[i] = bitmap[i] | j;
                // We return i * 8 because the bitmap is 8 bit per section
                // + we need to advance based on the free bit * obj_size.
                return MemoryBlock{(void*)(&pool[i * 8 + (idx * obj_size)]), obj_size};
            }
            j = j >> 1;
            ++idx;
        }
    }
    return MemoryBlock{};
}

auto PoolAllocator::deallocate(const MemoryBlock block) -> void {
    ptr_t p = reinterpret_cast<ptr_t>(block.data);
    // Extract the 'i' and 'count' (used in allocate()).
    ptr_t idx = (p - (ptr_t)pool) / obj_size;
    u32 section = idx / 8;
    u32 count = (p - (ptr_t)&pool[section * 8]) / obj_size;
    u8 bit = 0b10000000;
    bit = bit >> count;
    bitmap[section] &= ~bit;
}

} // namespace amelia

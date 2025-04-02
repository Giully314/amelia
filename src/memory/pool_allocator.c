// src/memory/pool_allocator.c
#include <amelia/memory/pool_allocator.h>
#include <amelia/memory.h>
#include <amelia/algorithms/minmax.h>
#include <amelia/printf.h>


void pool_allocator_init(struct PoolAllocator *a, u64 alignment) {
    // TODO: Align memory based on objsize.
    // Steps: 
    // 1) objects should point to the first aligned memory address.
    // 2) the capacity should be computed based on the alignemnt of each
    //  object and space available.
    // 3) For each object we should store
    
    memzero((ptr_t)a->block.start, a->block.size);
    
    a->bitmap = (byte*)memory_align(a->block.start, alignment); 
    
    i32 capacity = a->block.size / a->obj_size; 

    // The bitmap will start from a->objects with size bitmap_size.
    // in bit.
    a->bitmap_size = max(capacity / 8, 1);
    
    a->pool = memory_align((void*)(a->bitmap + a->bitmap_size), alignment); 
    
    // Update capacity while keeping in mind that we take some space
    // for the bitmap.
    a->capacity = capacity - ((intptr_t)(a->pool) - (intptr_t)(a->block.start));
    
    a->bitmap_size = max(capacity / 8, 1);
}   

void* pool_allocator_get(struct PoolAllocator *a) {
    for (u32 i = 0; i < a->bitmap_size; i += 1) {
        // Iterate over the 8 bits.
        byte j = 0b10000000;
        u32 idx = 0;
        while (j != (byte)0) {
            if ((a->bitmap[i] & j) == 0) {
                a->bitmap[i] = a->bitmap[i] | j;
                // We return i * 8 because the bitmap is 8 bit per section
                // + we need to advance based on the free bit * obj_size.
                return (void*)(&a->pool[i * 8 + (idx * a->obj_size)]);
            }
            j = j >> 1;
            ++idx;
        }
    }
    return nullptr;
}

void pool_allocator_release(struct PoolAllocator *a, void *p) {
    // Extract the 'i' and 'count' (used in pool_allocator_get).
    ptr_t idx = ((ptr_t)p - (ptr_t)a->pool) / a->obj_size;    
    u32 section = idx / 8;
    u32 count = ((ptr_t)p - (ptr_t)&a->pool[section * 8]) / a->obj_size;
    u8 bit = 0b10000000;
    bit = bit >> count; 
    a->bitmap[section] &= ~bit;
}
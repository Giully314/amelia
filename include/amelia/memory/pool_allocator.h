// amelia/memory/pool_allocator.h
// PURPOSE:
//
// STRUCTS:
//  PoolAllocator: Manage pool of fixed size memory.
// DESCRIPTION:
//

#ifndef _AMELIA_MEMORY_POOL_ALLOCATOR_H
#define _AMELIA_MEMORY_POOL_ALLOCATOR_H

#include <amelia/basic_types.h>
#include <amelia/memory/mblock.h>

// An allocator with fixed size pool of objects.
// The block memory should have enough space for the bitmap (1 bit for each
// object) and the desired size pool.
typedef struct PoolAllocator {
	struct MemoryBlock block;

	// Size of a single obj in byte.
	u32 obj_size;

	// Bitmap which tracks which memory is available.
	// Each bit corresponds to an object in the pool.
	// 0 if the object can be used, 1 if it is in use.
	byte *bitmap;
	u16 bitmap_size;

	// Start of the pool.
	byte *pool;

	// Number of total objects.
	u32 capacity;
} PoolAllocator_t;

// Initialize the array of objects based on the obj_size.
// The allocator must be already initialized with the memory block and
// the obj size.
void pool_allocator_init(struct PoolAllocator *a, u64 alignment);

// Get a piece of memory. If no memory is available, return nullptr.
void *pool_allocator_get(struct PoolAllocator *a);

// Release memory.
void pool_allocator_release(struct PoolAllocator *a, void *p);

#define POOL_ALLOCATOR_INIT(mblock, size) \
	{ .block = mblock,                \
	  .obj_size = size,               \
	  .bitmap = nullptr,              \
	  .bitmap_size = 0,               \
	  .pool = nullptr,                \
	  .capacity = 0 }

#endif // _AMELIA_MEMORY_POOL_ALLOCATOR_H
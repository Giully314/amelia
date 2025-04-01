// amelia/memory/mblock.h
// PURPOSE: Define a block of contigous memory.
//
// STRUCTS:
//  MemoryBlock: Represent a block of contigous memory.
//
// DESCRIPTION:
//


#ifndef _AMELIA_MEMORY_MBLOCK_H
#define _AMELIA_MEMORY_MBLOCK_H

#include <amelia/basic_types.h>

struct MemoryBlock {
    void* start;
    u64 size;
};

// A null memory block has size=0.
#define MEMORY_BLOCK_NULL (struct MemoryBlock){.start=nullptr, .size=0}

#endif // _AMELIA_MEMORY_MBLOCK_H


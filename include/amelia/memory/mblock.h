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
    ptr_t start;
    ptr_t end;
};

// A null memory block has end=0.
#define MEMORY_BLOCK_NULL (MemoryBlock){.start=0, .end=0}

#endif // _AMELIA_MEMORY_MBLOCK_H


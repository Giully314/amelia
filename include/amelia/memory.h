// amelia/memory.h
// PURPOSE: Define constants and utilities for low level memory management.
//
// DESCRIPTION:
//  This module defines memory related info like page sizes, stack size and
//  available memory region. Also 2 primitives are provided for allocating/deallocating
//  memory pages each of 4KB in size.
//

#ifndef _AMELIA_MEMORY_H
#define _AMELIA_MEMORY_H

#include <amelia/peripherals/peripherals_base.h>

#define PAGE_SHIFT 12
#define TABLE_SHIFT 9
#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE (1 << PAGE_SHIFT)
#define SECTION_SIZE (1 << SECTION_SHIFT)

// First available memory that can be used. The memory from 0 to LOW_MEMORY
// is used by the OS for stack and initialization (4MB).
#define LOW_MEMORY (2 * SECTION_SIZE)

// Address representing the upper bound of the memory that we can use (the last
// MB is reserved for the system registers).
#define HIGH_MEMORY PERIPHERALS_MEMORY_START

#define STACK_SIZE (1 << 16)

#define PAGING_MEMORY (HIGH_MEMORY - LOW_MEMORY)
#define PAGING_PAGES (PAGING_MEMORY / PAGE_SIZE)

#ifndef __ASSEMBLER__

#include <amelia/basic_types.h>

void memzero(u64 src, u64 num_bytes);

// Get a free page of memory from the allocator.
// If no page is available return 0, otherwise return the memory
// address of the start of the page.
ptr_t memory_get_free_page();

// Release a page of memory.
void memory_free_page(ptr_t p);

#endif

#endif // _AMELIA_MEMORY_H

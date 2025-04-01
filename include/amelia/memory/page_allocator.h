// amelia/memory/page_allocator.h
// PURPOSE: Define a page allocator for physical memory.
//
// DESCRIPTION:
//  This page allocator handles the physical memory divided into pages.
//

#ifndef _AMELIA_MEMORY_PAGE_ALLOCATOR_H
#define _AMELIA_MEMORY_PAGE_ALLOCATOR_H

#include <amelia/basic_types.h>
#include <amelia/memory/mblock.h>

// Get a free page of memory from the allocator.
// If no page is available return 0, otherwise return the memory
// address of the start of the page.
struct MemoryBlock memory_get_page();

// Release a page of memory.
void memory_free_page(void *p);


#endif // _AMELIA_MEMORY_PAGE_ALLOCATOR_H
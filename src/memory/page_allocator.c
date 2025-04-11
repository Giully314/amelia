// src/memory/page_allocator.c

#include <amelia/memory.h>
#include <amelia/memory/page_allocator.h>
#include <amelia/printf.h>

static u16 mem_map[PAGING_PAGES] = {
	0,
};

struct MemoryBlock memory_get_page()
{
	for (i32 i = 0; i < PAGING_PAGES; ++i) {
		if (mem_map[i] == 0) {
			mem_map[i] = 1;
			void *start = (void *)(LOW_MEMORY + i * PAGE_SIZE);
			return (struct MemoryBlock){ .start = start,
						     .size = PAGE_SIZE };
		}
	}
	return MEMORY_BLOCK_NULL;
}

void memory_free_page(void *p)
{
	mem_map[((ptr_t)p - LOW_MEMORY) / PAGE_SIZE] = 0;
}
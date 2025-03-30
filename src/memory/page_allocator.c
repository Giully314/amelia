// src/memory/page_allocator.c

#include <amelia/memory/page_allocator.h>
#include <amelia/memory.h>

static u16 mem_map[PAGING_PAGES] = {
	0,
};

struct MemoryBlock memory_get_page()
{
	for (u32 i = 0; i < PAGING_PAGES; ++i) {
		if (mem_map[i] == 0) {
			mem_map[i] = 1;
            ptr_t start = (LOW_MEMORY + i * PAGE_SIZE);
			return (struct MemoryBlock){.start=start, 
                .size=PAGE_SIZE};
		}
	}
	return (struct MemoryBlock){.start=0, .start=0};
}

void memory_free_page(ptr_t p)
{
	mem_map[(p - LOW_MEMORY) / PAGE_SIZE] = 0;
}
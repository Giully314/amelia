// src/memory.c
#include <amelia/basic_types.h>
#include <amelia/memory.h>

static u16 mem_map[PAGING_PAGES] = {
	0,
};

ptr_t memory_get_free_page()
{
	for (u32 i = 0; i < PAGING_PAGES; ++i) {
		if (mem_map[i] == 0) {
			mem_map[i] = 1;
			return LOW_MEMORY + i * PAGE_SIZE;
		}
	}
	return 0;
}

void memory_free_page(ptr_t p)
{
	mem_map[(p - LOW_MEMORY) / PAGE_SIZE] = 0;
}
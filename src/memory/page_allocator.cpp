// src/memory/page_allocator.cpp

#include <amelia/memory/page_allocator.hpp>

#include <amelia/types.hpp>

namespace amelia {
auto PageAllocator::allocate() -> MemoryBlock {
    for(i32 i = 0; i < PAGING_PAGES; ++i) {
        if(!PageAllocator::mem_map[i]) {
            PageAllocator::mem_map[i] = true;
            void *start = (void *)(LOW_MEMORY + i * PAGE_SIZE);
            return MemoryBlock{start, PAGE_SIZE};
        }
    }
    return MemoryBlock{};
}

auto PageAllocator::deallocate(MemoryBlock block) -> void {
    mem_map[((ptr_t)(block.data) - LOW_MEMORY) / PAGE_SIZE] = false;
}

} // namespace amelia

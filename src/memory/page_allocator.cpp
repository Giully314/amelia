// src/memory/page_allocator.cpp

#include <amelia/memory/page_allocator.hpp>

#include <amelia/types.hpp>

namespace amelia {
auto PageAllocator::allocate(const u64) -> MemoryBlock {
    for(i32 i = 0; i < PAGING_PAGES; ++i) {
        if(!PageAllocator::mem_map[i]) {
            PageAllocator::mem_map[i] = true;
            void *start = reinterpret_cast<void *>(LOW_MEMORY + i * PAGE_SIZE);
            return MemoryBlock{start, PAGE_SIZE};
        }
    }
    return MemoryBlock{};
}

auto PageAllocator::deallocate(const MemoryBlock block) -> void {
    mem_map[(reinterpret_cast<ptr_t>(block.data) - LOW_MEMORY) / PAGE_SIZE] = false;
}

} // namespace amelia

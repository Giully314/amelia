// amelia/memory/page_allocator.hpp
// PURPOSE:
//
// CLASSES:
//
// DESCRIPTION:
//
#pragma once

#include <amelia/hardware/platform_config.hpp>
#include <amelia/memory/block.hpp>

namespace amelia {

class PageAllocator {
public:
    static auto allocate() -> MemoryBlock;
    static auto deallocate(MemoryBlock block) -> void;

private:
    inline static bool mem_map[PAGING_PAGES]{false};
};

} // namespace amelia

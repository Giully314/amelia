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
    [[nodiscard]]
    static auto allocate([[maybe_unused]] const u64 = 0) -> MemoryBlock;
    static auto deallocate(const MemoryBlock block) -> void;

private:
    inline static bool mem_map[PAGING_PAGES]{false};
};

} // namespace amelia

// amelia/kernel/fork.hpp
// PURPOSE: Define process related operations.
//
// DESCRIPTION:
//
//

#pragma once

#include <amelia/kernel/task.hpp>
#include <amelia/memory/page_allocator.hpp>

namespace amelia {

struct Fork {
    auto copy_process(u64 func, u64 arg) -> void;
};

} // namespace amelia

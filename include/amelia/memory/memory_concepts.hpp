// amelia/memory/memory_concepts.hpp
// PURPOSE: Define memory allocators API.
//
// DESCRIPTION:
//
//

#include <concepts>
#include <amelia/memory/block.hpp>
#include <amelia/types.hpp>

namespace amelia {

template<typename T>
concept raw_allocator = requires(T a, u64 size, MemoryBlock block) {
    { a.allocate(size) } -> std::same_as<MemoryBlock>;
    { a.deallocate(block) };
}

} // namespace amelia

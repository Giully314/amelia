// amelia/memory/memory_concepts.hpp
// PURPOSE: Define memory allocators API.
//
// DESCRIPTION:
//
//

#include <amelia/concepts.hpp>
#include <amelia/memory/block.hpp>
#include <amelia/types.hpp>

namespace amelia {

template<typename T>
concept RawAllocator = requires(T a, u64 size, MemoryBlock block) {
    { a.allocate(size) } -> SameAs<MemoryBlock>;
    { a.deallocate(block) };
};

} // namespace amelia

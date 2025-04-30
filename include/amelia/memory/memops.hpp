// amelia/memory/memops.hpp
// PURPOSE:
//
// DESCRIPTION:

#pragma once

#include <amelia/types.hpp>

extern "C" {
// Fill a region of memory with 0.
// p is a pointer to the memory region.
// size is the number of bytes of the region.
auto memzero(void *p, amelia::u64 size) -> void;

// This function is not optimized.
inline auto memcpy(void *dst, const void *src, amelia::u64 num_bytes) -> void {
    const amelia::byte *s = static_cast<const amelia::byte *>(src);
    amelia::byte *d = static_cast<amelia::byte *>(dst);
    for(amelia::u64 i = 0; i < num_bytes; ++i) { d[i] = s[i]; }
}

inline auto memalign(void *p, const amelia::u64 alignment) -> void * {
    return reinterpret_cast<void *>((reinterpret_cast<amelia::ptr_t>(p) - 1u + alignment)
                                    & -alignment);
}

} // extern "C"
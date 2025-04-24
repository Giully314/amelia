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
auto memzero(void *p, u64 size) -> void;

// This function is not optimized.
inline auto memcpy(void *dst, const void *src, amelia::u64 num_bytes) {
    const amelia::byte *s = static_cast<const byte *>(src);
    amelia::byte *d = static_cast<byte *>(dst);
    for(u64 i = 0; i < num_bytes; ++i) {
        d[i] = s[i];
    }
}

inline auto mem_align(void *p, const amelia::u64 alignment) {
    return static_cast<void *>((static_cast<amelia::ptr_t>(p) - 1u + alignment) & -alignment);
}

} // extern "C"
// src/memory.c

#include <amelia/memory.h>

void* memory_align(void *p, u64 alignment) {
    const ptr_t aligned = ((ptr_t)p - 1u + alignment) & -alignment;
    return (void*)aligned;
}

// src/memory.c

#include <amelia/memory.h>

void *memory_align(void *p, u64 alignment)
{
	const ptr_t aligned = ((ptr_t)p - 1u + alignment) & -alignment;
	return (void *)aligned;
}

// This function is not optimized.
void memcpy(void *src, void *dst, u64 num_bytes)
{
	// If num_bytes is a multiple of u64, copy in blocks of 8 bytes.
	// if (num_bytes >= 8 && (num_bytes % sizeof(u64) == 0)) {
	// 	u64 i = 0;
	// 	u64 *s = (u64 *)src;
	// 	u64 *d = (u64 *)dst;

	// 	for (; i < num_bytes / sizeof(u64); i += sizeof(u64)) {
	// 		d[i] = s[i];
	// 	}
	// } else if (num_bytes >= 4 &&
	// 	   (num_bytes % sizeof(u32) == 0)) { // block of 4 bytes.
	// 	u64 i = 0;
	// 	u32 *s = (u32 *)src;
	// 	u32 *d = (u32 *)dst;

	// 	for (; i < num_bytes / sizeof(u32); i += sizeof(u32)) {
	// 		d[i] = s[i];
	// 	}
	// } else { // copy 1 byte at time.
	byte *s = (byte *)src;
	byte *d = (byte *)dst;

	for (u64 i = 0; i < num_bytes; ++i) {
		d[i] = s[i];
	}
}

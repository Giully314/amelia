// amelia/memory/memops.hpp
// PURPOSE:
//
// DESCRIPTION:

#pragma once

extern "C" {
// Fill a region of memory with 0.
// p is a pointer to the memory region.
// size is the number of bytes of the region.
void memzero(void *p, unsigned long long size);

} // extern "C"
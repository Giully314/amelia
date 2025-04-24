// amelia/hardware/platform_config.hpp
// PURPOSE: Define platform dependent constant for the OS.
//
#pragma once

#include <amelia/hardware/memory_config.hpp>

#define PAGE_SHIFT 12
#define TABLE_SHIFT 9
#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE (1 << PAGE_SHIFT)
#define SECTION_SIZE (1 << SECTION_SHIFT)

// First available memory that can be used. The memory from 0 to LOW_MEMORY
// is used by the OS for stack and initialization (4MB).
#define LOW_MEMORY (2 * SECTION_SIZE)

// Address representing the upper bound of the memory that we can use (the last
// MB is reserved for the system registers).
#define HIGH_MEMORY PERIPHERALS_MEMORY_START

#define STACK_SIZE (1 << 16)

#define PAGING_MEMORY (HIGH_MEMORY - LOW_MEMORY)
#define PAGING_PAGES (PAGING_MEMORY / PAGE_SIZE)

#define INT_VEC_TABLE_ADDRESS 0x0
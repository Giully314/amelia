// amelia/memory.h
// PURPOSE:
//
// DESCRIPTION:
//

#ifndef _AMELIA_MEMORY_H
#define _AMELIA_MEMORY_H

#define PAGE_SHIFT 12
#define TABLE_SHIFT 9
#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE (1 << PAGE_SHIFT)
#define SECTION_SIZE (1 << SECTION_SHIFT)

#define LOW_MEMORY (2 * SECTION_SIZE)

#ifndef __ASSEMBLER__

void memzero(unsigned long src, unsigned long num_bytes);

#endif

#endif  // _AMELIA_MEMORY_H

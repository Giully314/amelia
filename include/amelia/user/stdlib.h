// amelia/user/stdlib.h
// PURPOSE:
//
// DESCRIPTION:
//
//

#ifndef _AMELIA_USER_STDMEM_H
#define _AMELIA_USER_STDMEM_H

// Return a page of physical memory.
void *page_malloc();

// Correct termination of a process.
void exit();

// void fork();

#endif // _AMELIA_USER_STDMEM_H
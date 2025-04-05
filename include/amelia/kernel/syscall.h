// amelia/kernel/syscall.h
// PURPOSE: Define system call.
//
// DESCRIPTION:
//  System calls are functions exposed to user programs to execute code at higher level
//  of permissions (OS is at el1).
//  This file
//

#ifndef _AMELIA_KERNEL_SYSCALL_H
#define _AMELIA_KERNEL_SYSCALL_H

#define SYS_WRITE_NUMBER 0
#define SYS_MALLOC_NUMBER 1
#define SYS_FORK_NUMBER 2
#define SYS_EXIT_NUMBER 3

#define __NR_syscall 4

#ifndef __ASSEMBLER__

#include <amelia/basic_types.h>

// Write a buffer.
void sys_write(char *buffer);

// Fork a process.
i32 sys_fork();

// Return a page of memory.
void *sys_malloc();

// Correct exit of a user process.
void sys_exit();

#endif // __ASSEMBLER__

#endif // _AMELIA_KERNEL_SYSCALL_H
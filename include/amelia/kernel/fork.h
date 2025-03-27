// amelia/kernel/fork.h
// PURPOSE: Define API system call for the creation of new tasks.
//
// DESCRIPTION:
//  The implementation is heavily inspired by the Linux kernel.
//  The creation of a new task is based on the copy of the current one. 
//

#ifndef _AMELIA_KERNEL_FORK_H
#define _AMELIA_KERNEL_FORK_H

#include <amelia/basic_types.h>

// Create a new priority task, 
// with function (a pointer to a function) to execute
// by passing arg as a pointer to the args.
// Return 0 on success.
i32 start_process_with_priority(ptr_t function, ptr_t arg, i32 priority);

// Create a new task with the same priority as the caller task.
i32 start_process(ptr_t function, ptr_t arg);

#endif // _AMELIA_KERNEL_FORK_H
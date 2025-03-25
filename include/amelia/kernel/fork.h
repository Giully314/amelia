// amelia/kernel/fork.h
// PURPOSE:
//
// DESCRIPTION:
//

#ifndef _AMELIA_KERNEL_FORK_H
#define _AMELIA_KERNEL_FORK_H

#include <amelia/basic_types.h>

// Create a new task with function (a pointer to a function) to execute
// by passing arg as a pointer to the args.
// Return 0 on success.
i32 start_process(ptr_t function, ptr_t arg);

#endif // _AMELIA_KERNEL_FORK_H
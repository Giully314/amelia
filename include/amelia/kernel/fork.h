// amelia/kernel/fork.h
// PURPOSE: Define low level API for forking a task.
//
// DESCRIPTION:
//  The implementation is heavily inspired by the Linux kernel.
//  The creation of a new task is based on the copy of the current one.
//  These routines (with prefix k which stands for kernel) are used
//  internally by the kernel for low level task creation.
//  To access these functionalities from an higher level, use syscall.
//

#ifndef _AMELIA_KERNEL_FORK_H
#define _AMELIA_KERNEL_FORK_H

#include <amelia/basic_types.h>
#include <amelia/hardware/cpu.h>
#include <amelia/kernel/task.h>

// Kernel fork.
// Create a new priority task,
// with function (a pointer to a function) to execute
// by passing arg as a pointer to the args.
// Return 0 on success.
i32 kfork_with_priority(u64 fork_flag, ptr_t fn, ptr_t arg, u32 priority,
			u64 stack);

// Create a new task with the same priority as the caller task.
i32 kfork(u64 fork_flag, ptr_t fn, ptr_t arg, u64 stack);

// Move a process to EL0.
// pc is the program counter.
// Return 0 on success.
i32 move_to_user_mode(u64 pc);

struct ProcessTraceRegs *task_pt_regs(struct Task *task);

#endif // _AMELIA_KERNEL_FORK_H
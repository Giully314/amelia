// amelia/kernel/task.h
// PURPOSE: Define information for a task.
//
// STRUCTS:
//  ProcessInfo:
//
// DESCRIPTION:
//	A task is a program that is executed by the CPU. In this context the difference
//	between process and thread is not relevant.
//

#ifndef _AMELIA_KERNEL_TASK_H
#define _AMELIA_KERNEL_TASK_H

#include <amelia/basic_types.h>
#include <amelia/hardware/cpu.h>

#define TASK_KERNEL_THREAD 0x1ul

typedef enum TaskState {
	TASK_RUNNING, // The thread is running.
	TASK_READY, // The thread is ready to run.
	TASK_BLOCKED, // The thread is in a blocked state.
	TASK_ZOMBIE, // the task finished its execution and now wait to be released.
} TaskState;

typedef struct Task {
	struct CPUContext cpu_context;
	enum TaskState state;

	// How many ticks the task should run.
	i32 counter;

	// Priority assigned at task creation. This number is used for comparison
	// with other tasks for priority execution.
	i32 priority;

	// Current priority of the task. This number is based on the priority
	// field but it is modiefied by the scheduler for reassessing the process
	// priority to avoid cpu monopoly.
	// This is copied to counter. It signals how much a task must run
	// based on its priority.
	// i32 current_priority;

	// Non-zero value means the task cannot be preempted.
	// TODO: change this to a bool value, to avoid problems in case
	// we increment 2 consecutive times this value through scheduler_preempt_enable().
	i32 preempt_count;

	u64 stack;
	u64 flags;

	u64 pid;
} Task;

#endif // AMELIA_KERNEL_TASK_H

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

typedef enum TaskState {
	TASK_READY, // The thread is ready to run.
	TASK_RUNNING, // The thread is running.
	TASK_BLOCKED, // The thread is in a blocked state.
} TaskState;

typedef struct Task {
	struct CPUContext cpu_context;
	enum TaskState state;

	// How many ticks the task should run.
	u32 counter;

	// This is copied to counter. It signals how much a task must run
	// based on its priority.
	u32 priority;

	// Non-zero value means the task cannot be preempted.
	u32 preempt_count;
} Task;

#endif // AMELIA_KERNEL_TASK_H

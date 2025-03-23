// amelia/kernel/process.h
// PURPOSE: Define the structs for information about a process.
//
// STRUCTS:
//  ProcessInfo:
//
// DESCRIPTION:
//
#ifndef AMELIA_KERNEL_PROCESS_H
#define AMELIA_KERNEL_PROCESS_H

#include <stdint.h>

typedef enum ThreadState {
	READY, // The thread is ready to run.
	RUNNING, // The thread is running.
	BLOCKED, // The thread is in a blocked state.
} ExecutionState;

// Represent a thread of execution.
typedef struct Thread {
	int32_t id;
	// Program counter, registers, stack, state
} Thread;

// Save the state of a running process.
typedef struct ProcessInfo {
	int32_t id;

	Thread *threads;

	// Address space.

	// Info related to process management.

	// Info related to memory.

	// Info related to files.

} ProcessInfo;

#endif

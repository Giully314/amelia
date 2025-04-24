// amelia/kernel/task.hpp
// PURPOSE: Define information for a task.
//
// STRUCTS:
//  ProcessInfo:
//
// DESCRIPTION:
//	A task is a program that is executed by the CPU. In this context the difference
//	between process and thread is not relevant.
//
#pragma once

#include <amelia/hardware/cpu.hpp>
#include <amelia/types.hpp>

#define TASK_KERNEL_THREAD 0x1ul

namespace amelia {
enum class TaskState : u8 {
    Running, // The thread is running.
    Ready,   // The thread is ready to run.
    Blocked, // The thread is in a blocked state.
    Zombie,  // the task finished its execution and now wait to be released.
};

struct Task {
    CPUContext cpu_context;
    TaskState state;

    // How many ticks the task should run.
    i32 counter;

    // Priority assigned at task creation. This number is used for comparison
    // with other tasks for priority execution.
    i32 priority;

    bool preempt;

    u64 pid;
};
} // namespace amelia

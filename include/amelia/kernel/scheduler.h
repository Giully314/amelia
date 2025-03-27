// amelia/kernel/scheduler.h
// PURPOSE:
//
// DESCRIPTION:
//

#ifndef _AMELIA_KERNEL_SCHEDULER_H
#define _AMELIA_KERNEL_SCHEDULER_H

#define THREAD_CPU_CONTEXT 0

#ifndef __ASSEMBLER__

#include <amelia/basic_types.h>
#include <amelia/kernel/task.h>

#define MAX_NUMBER_OF_TASKS 64

#define THREAD_SIZE 4096

#define FIRST_TASK tasks[0]
#define LAST_TASK tasks[MAX_NUMBER_OF_TASKS - 1]

extern Task *current_task;
extern Task *tasks[MAX_NUMBER_OF_TASKS];

// Current number of tasks.
extern u32 size_tasks;

// Initialize the scheduler.
void scheduler_init();

void scheduler_schedule();

void scheduler_timer_tick();

// Enable preempting. The scheduler can stop a task and scheduler another.
void scheduler_preempt_enable();

// Disable preempting, a task cannot be interrupted.
void scheduler_preempt_disable();

void scheduler_switch_to(struct Task *next);

void scheduler_cpu_switch_to(struct Task *prev, struct Task *next);

void ret_from_fork();

// clang-format off
#define INIT_TASK \
/*cpu_context*/	{ {0,0,0,0,0,0,0,0,0,0,0,0,0}, \
/* state etc */	TASK_RUNNING,0,1,1,0 \
}
// clang-format on

#endif // __ASSEMBLER__
#endif // _AMELIA_KERNEL_SCHEDULER_H
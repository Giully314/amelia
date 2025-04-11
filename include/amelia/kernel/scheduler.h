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

void scheduler_add_task(struct Task *t);

struct Task *scheduler_current_task();

// Release memory associated with a task. The task (following Linux approach)
// is not deleted but it is put in zombie mode to avoid to be selected
// by the scheduler for running.
void scheduler_exit_process();

// clang-format off
#define INIT_TASK \
/*cpu_context*/	{ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, \
/* state etc */	TASK_RUNNING,0,1,0, 0, TASK_KERNEL_THREAD, 1 \
}
// clang-format on

#endif // __ASSEMBLER__
#endif // _AMELIA_KERNEL_SCHEDULER_H
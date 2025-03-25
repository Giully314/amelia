// src/kernel/scheduler.c
// DESCRIPTION:
//

#include <amelia/kernel/scheduler.h>
#include <amelia/kernel/task.h>

// Setup the list of tasks and initialize the first task.

static struct Task init_task = INIT_TASK;

// Current task in execution.
struct Task *current_task = &init_task;

// For now the list of tasks is fixed to 64.
struct Task *tasks[MAX_NUMBER_OF_TASKS] = {
	&init_task,
}

u32 size_tasks = 1;

void scheduler_schedule_tail()
{
	scheduler_preempt_enable();
}
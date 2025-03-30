// src/kernel/scheduler.c
// DESCRIPTION:
//

#include <amelia/kernel/scheduler.h>
#include <amelia/kernel/task.h>
#include <amelia/peripherals/irq.h>
#include <amelia/printf.h>

// Setup the list of tasks and initialize the first task.

static struct Task init_task = INIT_TASK;

// Current task in execution.
struct Task *current_task = &init_task;

// For now the list of tasks is fixed to 64.
struct Task *tasks[MAX_NUMBER_OF_TASKS];

u32 size_tasks = 1;

// This algorithm is almost a copy of the scheduler algorithm found in the
// first linux version.
// This function MUST be executed when interrupts are enabled to avoid
// infinite loops because if all the tasks are in a wait state, we need some way
// to change the state. There is no problem for race conditions (reading the state
// while writing to it) because right now the OS is single core and the interrupts
// are executed by the same core running this function.
void _schedule()
{
	scheduler_preempt_disable();
	u32 next = 0;
	i32 c = 0;
	struct Task *t;

	while (1) {
		c = -1;
		next = 0;
		// Get the task with the higher counter; this means this task
		// is the one who execution time was the least among the others.
		for (u32 i = 0; i < MAX_NUMBER_OF_TASKS; ++i) {
			t = tasks[i];

			if (t && t->state == TASK_RUNNING && t->counter > c) {
				c = t->counter;
				next = i;
			}
		}

		// If a task respecting the previous rule is found, schedule it.
		if (c) {
			break;
		}

		// Execute this function only if all the tasks are in a 0 counter
		// state or are not in a running state.
		for (u32 i = 0; i < MAX_NUMBER_OF_TASKS; ++i) {
			t = tasks[i];
			if (t) {
				t->counter = (t->counter >> 1) + t->priority;
			}
		}
	}
	scheduler_switch_to(tasks[next]);
	scheduler_preempt_enable();
}

void scheduler_init()
{
	tasks[0] = &init_task;
	size_tasks = 1;
	for (u32 i = 1; i < MAX_NUMBER_OF_TASKS; ++i) {
		tasks[i] = nullptr;
	}
}

void scheduler_schedule_tail()
{
	scheduler_preempt_enable();
}

void scheduler_timer_tick()
{
	--current_task->counter;
	if (current_task->counter > 0 || current_task->preempt_count > 0) {
		return;
	}

	current_task->counter = 0;
	
	irq_enable();
	_schedule();
	irq_disable();
}

void scheduler_preempt_enable()
{
	--current_task->preempt_count;
}

void scheduler_preempt_disable()
{
	++current_task->preempt_count;
}

void scheduler_switch_to(struct Task *next)
{
	if (current_task == next) {
		return;
	}
	struct Task *prev = current_task;
	current_task = next;
	scheduler_cpu_switch_to(prev, next);
}

void scheduler_schedule()
{
	current_task->counter = 0;
	_schedule();
}
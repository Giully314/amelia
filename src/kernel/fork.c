// src/kernel/fork.c

#include <amelia/kernel/fork.h>
#include <amelia/kernel/scheduler.h>
#include <amelia/kernel/task.h>
#include <amelia/memory.h>

i32 start_process(ptr_t function, ptr_t arg)
{
	// This function cannot be interrupted, so we need
	// to disable preempting.
	scheduler_preempt_disable();
	struct Task *t;

	t = memory_get_free_page();
	if (!t) {
		return 1;
	}

	t->priority = current_task->priority;
	t->state = TASK_RUNNING;
	t->counter = t->priority;
	// Disable preemption.
	t->preempt_count = 1;

	t->cpu_context.x19 = function;
	t->cpu_context.x20 = arg;
	t->cpu_context.pc = ret_from_fork;
	t->cpu_context.sp = t + THREAD_SIZE;

	i32 pid = size_tasks++;
	tasks[pid] = t;
	scheduler_preempt_enable();

	return 0;
}

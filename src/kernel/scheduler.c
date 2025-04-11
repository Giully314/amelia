// src/kernel/scheduler.c
// DESCRIPTION:
//	The execution of the scheduler right now is simple, each time the queue
// 	of tasks to be executed is empty, the scheduler re assign to each task
//	a new counter of execution.
//

#include <amelia/ds/dl_list.h>
#include <amelia/ds/rb_tree.h>
#include <amelia/kernel/scheduler.h>
#include <amelia/kernel/task.h>
#include <amelia/memory.h>
#include <amelia/memory/page_allocator.h>
#include <amelia/memory/pool_allocator.h>
#include <amelia/peripherals/irq.h>
#include <amelia/printf.h>

// This is temporary.
static u64 next_pid = 2;

// The Scheduler struct is responsible to schedule tasks on a single cpu.
// Each cpu has its own Scheduler with its internal queue of tasks.
// For now there is only 1 cpu in usage, so things are simple, but for
// multiple cpu, we need to use a lock for accessing this class to enable task
// assignment to each scheduler and possibly task stealing to balance the workload.
// In future there will be another layer of abstraction for assigning task to cpu
// after the scheduler execution, called the task dispatcher.
struct Scheduler {
	struct DLList task_list;

	struct Task *current_task;
	struct PoolAllocator list_alloc;

	// Page of memory used by the allocators.
	struct MemoryBlock page;
};

struct Scheduler sched;

void scheduler_init()
{
	sched.page = memory_get_page();
	// sched.list_alloc.block = sched.page doesn't work, it raises el1h exception.
	// Why?
	sched.list_alloc.block.start = sched.page.start;
	sched.list_alloc.block.size = sched.page.size;

	sched.list_alloc.obj_size = sizeof(struct DLNode);
	pool_allocator_init(&sched.list_alloc, 8);

	sched.task_list.alloc = &sched.list_alloc;

	sched.current_task = (struct Task *)memory_get_page().start;
	struct Task init_task = (struct Task)INIT_TASK;
	memcpy((void *)&init_task, (void *)sched.current_task,
	       sizeof(struct Task));

	dl_list_push_back(&sched.task_list, (void *)sched.current_task);
}

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
	i32 c = 0;
	struct Task *t;
	struct Task *next;

	while (1) {
		c = -1;
		next = 0;
		// Get the task with the higher counter; this means this task
		// is the one who execution time was the least among the others.
		struct DLNode *curr = sched.task_list.first;
		while (curr != nullptr) {
			t = curr->data;
			if (t->state == TASK_RUNNING && t->counter > c) {
				c = t->counter;
				next = t;
			}
			curr = curr->next;
		}

		// If a task respecting the previous rule is found, schedule it.
		if (c) {
			break;
		}

		// Execute this function only if all the tasks are in a 0 counter
		// state or are not in a running state.
		curr = sched.task_list.first;
		while (curr != nullptr) {
			t = curr->data;
			t->counter = (t->counter >> 1) + t->priority;
			curr = curr->next;
		}
	}
	scheduler_switch_to(next);
	scheduler_preempt_enable();
}

void scheduler_schedule_tail()
{
	scheduler_preempt_enable();
}

void scheduler_timer_tick()
{
	struct Task *current_task = sched.current_task;
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
	--sched.current_task->preempt_count;
}

void scheduler_preempt_disable()
{
	++sched.current_task->preempt_count;
}

void scheduler_switch_to(struct Task *next)
{
	if (sched.current_task == next) {
		return;
	}
	struct Task *prev = sched.current_task;
	sched.current_task = next;
	scheduler_cpu_switch_to(prev, next);
}

void scheduler_schedule()
{
	sched.current_task->counter = 0;
	_schedule();
}

void scheduler_add_task(struct Task *t)
{
	t->pid = next_pid++;
	dl_list_push_back(&sched.task_list, (void *)t);
}

struct Task *scheduler_current_task()
{
	return sched.current_task;
}

void scheduler_exit_process()
{
	scheduler_preempt_disable();

	struct DLNode *current = sched.task_list.first;
	struct Task *t = nullptr;

	while (current != nullptr) {
		t = (struct Task *)current->data;
		if (t == sched.current_task) {
			t->state = TASK_ZOMBIE;
			break;
		}
		current = current->next;
	}

	if (sched.current_task->stack) {
		memory_free_page((void *)sched.current_task->stack);
	}

	scheduler_preempt_enable();
	scheduler_schedule();
}
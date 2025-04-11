// src/kernel/fork.c

#include <amelia/arm/sysregs.h>
#include <amelia/kernel/fork.h>
#include <amelia/kernel/scheduler.h>
#include <amelia/memory.h>
#include <amelia/memory/page_allocator.h>
#include <amelia/printf.h>

i32 kfork_with_priority(u64 fork_flag, ptr_t fn, ptr_t arg, u32 priority,
			u64 stack)
{
	// This function cannot be interrupted, so we need
	// to disable preempting.
	scheduler_preempt_disable();
	struct MemoryBlock block = memory_get_page();
	if (block.start == nullptr) {
		return 0;
	}
	struct Task *t = (struct Task *)block.start;

	struct Task *current = scheduler_current_task();

	struct ProcessTraceRegs *childregs = task_pt_regs(t);
	memzero((ptr_t)childregs, sizeof(struct ProcessTraceRegs));
	memzero((ptr_t)&t->cpu_context, sizeof(struct CPUContext));

	if (fork_flag & TASK_KERNEL_THREAD) {
		t->cpu_context.x19 = fn;
		t->cpu_context.x20 = arg;
	} else {
		struct ProcessTraceRegs *curr_regs = task_pt_regs(current);
		*childregs = *curr_regs;
		childregs->regs[0] = 0;
		childregs->sp = stack + PAGE_SIZE;
		t->stack = stack;
	}

	t->flags = fork_flag;
	t->priority = priority;
	t->state = TASK_RUNNING;
	t->counter = priority;
	t->preempt_count = 1; // disable preemtion until schedulu tail.

	t->cpu_context.pc = (u64)ret_from_fork;
	t->cpu_context.sp = (u64)childregs;

	scheduler_add_task(t);
	scheduler_preempt_enable();

	return (i32)t->pid;
}

i32 kfork(u64 fork_flag, ptr_t fn, ptr_t arg, u64 stack)
{
	return kfork_with_priority(fork_flag, fn, arg,
				   scheduler_current_task()->priority, stack);
}

i32 move_to_user_mode(u64 pc)
{
	struct Task *current = scheduler_current_task();
	struct ProcessTraceRegs *regs = task_pt_regs(current);
	memzero((ptr_t)regs, sizeof(*regs));
	regs->pc = pc;
	regs->pstate = PSR_MODE_EL0t;
	void *stack = memory_get_page().start;
	if (!stack) {
		return -1;
	}

	regs->sp = (u64)stack + PAGE_SIZE;
	current->stack = (u64)stack;
	return 0;
}

struct ProcessTraceRegs *task_pt_regs(struct Task *task)
{
	ptr_t p = (ptr_t)task + THREAD_SIZE - sizeof(struct ProcessTraceRegs);
	return (struct ProcessTraceRegs *)p;
}
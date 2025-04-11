// src/kernel/syscall.c
#include <amelia/kernel/fork.h>
#include <amelia/kernel/scheduler.h>
#include <amelia/kernel/syscall.h>
#include <amelia/memory/page_allocator.h>
#include <amelia/printf.h>

void sys_write(char *buffer)
{
	printf(buffer);
}

void *sys_malloc()
{
	// TODO: return a memory block instead of only a pointer.
	struct MemoryBlock m = memory_get_page();
	if (m.size == 0) {
		return nullptr;
	}

	return m.start;
}

i32 sys_create_process(u64 stack)
{
	return kfork(0, 0, 0, stack);
}

void sys_exit()
{
	scheduler_exit_process();
}

void *sys_call_table[] = { sys_write, sys_malloc, sys_create_process,
			   sys_exit };
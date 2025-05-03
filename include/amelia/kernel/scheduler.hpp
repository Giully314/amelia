// amelia/kernel/scheduler.hpp
// PURPOSE: Define a scheduler for tasks.
//
// CLASSES:
//  Scheduler: Linux based scheduler for tasks.
//
// DESCRIPTION:
//  This component handles the task to be executed in the system by scheduling and switching them on
//  timer interrupts.
//

#pragma once

#include <amelia/ds/dl_list.hpp>
#include <amelia/kernel/task.hpp>
#include <amelia/memory/pool_allocator.hpp>

namespace amelia {

class Scheduler {
public:
    Scheduler();

    static auto instance() -> Scheduler& {
        static Scheduler sched;
        return sched;
    }

    // Execute the schedule algorithm.
    // The call to this function doesn't imply that a new task is executed; this depends on
    // how many execution ticks the current task has left.
    auto schedule() -> void;

    auto preempt_enable() -> void;

    auto preempt_disable() -> void;

    auto add_task() -> void;

    auto current_task() const -> const Task&;

private:
private:
    PoolAllocator alloc;
    DLList<Task, PoolAllocator> tasks;
    Task* current_task;
}

} // namespace amelia

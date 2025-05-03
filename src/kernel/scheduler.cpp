// src/kernel/scheduler.cpp

#include <amelia/kernel/scheduler.hpp>

#include <amelia/memory/page_allocator.hpp>

namespace amelia {

Scheduler::Scheduler(): alloc{PageAllocator::allocate()}, tasks{alloc} {}

} // namespace amelia

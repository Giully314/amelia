// amelia/kernel/scheduler.hpp
// PURPOSE: Define task schedueler.
//
// CLASSES:
//
// DESCRIPTION:
//

#pragma once

#include <amelia/ds/dl_list.hpp>
#include <amelia/kernel/task.hpp>

namespace amelia {

class Scheduler {
private:
    DLList<Task> tasks;
}

} // namespace amelia

#pragma once

#include "tasks/task-scheduler.h"


namespace tasks
{
    namespace schedulers
    {
        /// <summary>
        /// Creates a scheduler that performs each task in parallel (one thread per task).
        /// </summary>
        TaskScheduler naive_parallel();
    }
}
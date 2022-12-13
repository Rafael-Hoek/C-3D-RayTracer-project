#include "tasks/naive-parallel-task-scheduler.h"
#include "easylogging++.h"



using namespace tasks;


namespace
{
    /// <summary>
    /// Performs each task in parallel (one thread per task).
    /// </summary>
    class NaiveParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
    {
    public:


        void perform(std::vector<std::shared_ptr<Task>> tasks) const
        {
            std::vector<std::thread> threads;
            
            for (auto task : tasks)
            {


                threads.push_back(std::thread([task]() {
                    task->perform();
                    }));
                



            }
            LOG(INFO) << "added threads to list";
            for (auto &th : threads) {
                th.join();
            }
            LOG(INFO) << "joined threads";

        }
    };
}

TaskScheduler tasks::schedulers::naive_parallel()
{
    LOG(INFO) << "Creating naive parallel scheduler";

    return TaskScheduler(std::make_shared<NaiveParallelTaskScheduler>());
}
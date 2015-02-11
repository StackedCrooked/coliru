
struct Worker
{
    Worker() : thread_([this]{ work(); })
    {   
    }   

    ~Worker()
    {   
        // nullptr is stop-signal
        queue_.push(nullptr);
        thread_.join();
    }   

    Worker(const Worker&) = delete;
    Worker& operator=(const Worker&) = delete;

    void work()
    {
        for (;;)
        {   
            Task* task;
            queue_.pop(task);
            
            if (!task) 
            {   
                // nullptr is stop-signal
                return;
            }   
            
            task->run();
        }   
    }   

    tbb::concurrent_bounded_queue<Task*> queue_;
    std::thread thread_;
};

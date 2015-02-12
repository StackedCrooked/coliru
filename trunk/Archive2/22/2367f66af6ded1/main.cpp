

struct Worker
{
    Worker() : thread_([this]{ work(); }) {    }   

    ~Worker()
    {   
        // nullptr is stop-signal
        task_queue.push(Task{});
        thread_.join();
    }   

    Worker(const Worker&) = delete;
    Worker& operator=(const Worker&) = delete;

    void work()
    {
        for (;;)
        {   
            Task task;
            task_queue.pop(task);
            
            if (!task) 
            {   
                // nullptr is stop-signal
                return;
            }   
            
            task();
        }   
    }   
    
    std::thread thread_;
};

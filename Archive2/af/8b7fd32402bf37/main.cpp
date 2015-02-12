#include "tbb/concurrent_queue.h"
#include <functional>
#include <iostream>
#include <thread>


using Task = std::function<void()>;
tbb::concurrent_bounded_queue<Task> task_queue;


struct Worker
{
    Worker() : thread_([this]{ work(); })
    {   
    }   

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


int main()
{
    {
        Worker worker[2];
        task_queue.push([]{ std::cout << "1" << std::flush; });
        task_queue.push([]{ std::cout << "2" << std::flush; });
        task_queue.push([]{ std::cout << "3" << std::flush; });
    }
    std::cout << "End of program." << std::endl;
}

#include "tbb/task.h"
#include <iostream>
#include <future>
#include <unistd.h>



template<typename F>
void run_in_background(F&& f)
{
    struct Task : tbb::task
    {
        Task(F f) : f_(std::move(f)) {}
    
        virtual tbb::task* execute()
        {
            f_();
            return nullptr;
        }
        
        F f_;
    };
    auto task = new (tbb::task::allocate_root()) Task(std::forward<F>(f));
    tbb::task::enqueue(*task);
}


int main()
{
    for (int i = 0; i != 10; ++i)
    {
        // launch a task that prints the current value of i
        run_in_background([i]{ std::cout << i << ' '; });
    }
    sleep(1);
}
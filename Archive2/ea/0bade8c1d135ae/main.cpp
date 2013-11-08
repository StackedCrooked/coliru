#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <queue>
#include <future>
#include <mutex>
#include <condition_variable>
 
class generic_task
{
public:
    virtual void operator()() = 0;
};

template<typename R, typename... Args>
class concrete_task : public generic_task
{
public:
    std::packaged_task<R(Args)...> packaged;

    concrete_task(R ret, Args&&... args) : packaged(ret, args...) {}
    virtual void operator()() { packaged(); }
};
 
class task_pool
{
public:
    task_pool() : thr(std::bind(&task_pool::run, this)), noExit(true) {}
    ~task_pool() { noExit = false; thr.join(); }
    
    template<typename R, typename... Args>
    inline std::future<R> push(R ret, Args&&... args)
    {
        concrete_task<R(Args)...> task(ret, args... );
        std::future<R> future = task.packaged.get_future();
        {
            std::unique_lock<std::mutex> lk(m);
            tasks.push_back(task);
        }
        
        return future;
    }

private:
    void run()
    {
        while(noExit)
        {
            if(tasks.empty())
            {
                std::unique_lock<std::mutex> lk(m);
                cv.wait(lk, [] {return !tasks.empty();});
            }
            
            auto task = tasks.front();
            task.pop_front();
            task();
        }
    }

    std::thread thr;
    std::queue<generic_task> tasks;
    
    bool noExit;
    
    std::mutex m;
    std::condition_variable cv;
};


int main()
{
    
}
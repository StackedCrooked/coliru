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
 
class TaskPool
{
public:
    TaskPool() : m_thread(std::bind(&TaskPool::run, this)), noExit(true) {}
    ~TaskPool() : { noExit = false; m_thread.join(); }
    
    template<typename T, typename... Args>
    inline std::future< std::result_of<decltype(T)(args)...> > add(T func, Args&&... args) {
        std::packaged_task<std::result_of<decltype(T)(args)...>()> task(std::bind( func(args)... ));
        auto future = task.get_future();
        {
            std::unique_lock<std::mutex> lk(m);
            tasks.push_back(std::move(task));
        }
        
        return future;
    }

private:
    void TaskPool::run()
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

    std::thread m_thread;
    std::queue<std::packaged_task<void()>> tasks;
    
    bool noExit;
    
    std::mutex m;
    std::condition_variable cv;
};


int main()
{
    
}
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
#include <memory>
 

class task_pool
{
public:
    task_pool() : thr(std::bind(&task_pool::run, this)), noExit(true) {}
    ~task_pool() { noExit = false; thr.join(); }

    template<typename R, typename F,  typename... Args>
    inline std::future<R> push(F func, Args&&... args)
    {
        auto task = new concrete_task<R(Args)...>(func, args... );
        std::future<R> future = task->packaged.get_future();
        {
            std::unique_lock<std::mutex> lk(m);
            tasks.push(std::unique_ptr<generic_task>(task));
            cv.notify_one();
        }
        
        return future;
    }

private:

    struct generic_task
    {
        virtual void operator()() = 0;
    };
    
    template<typename R, typename... Args>
    struct concrete_task : public generic_task
    {
        std::packaged_task<R(Args)...> packaged;
    
        template <class F> concrete_task(F func, Args&&... args) : packaged(func, args...) {}
        virtual void operator()() { packaged(); }
    };

    void run()
    {
        while(noExit)
        {
            if(tasks.empty())
            {
                std::unique_lock<std::mutex> lk(m);
                cv.wait(lk, [this] {return !tasks.empty();});
            }
            
            auto task = std::move(tasks.front());
            tasks.pop();
            (*task)();
        }
    }

    std::thread thr;
    std::queue<std::unique_ptr<generic_task>> tasks;
    
    std::mutex m;
    std::condition_variable cv;
    
    bool noExit;
};

int factorial(int i)
{
    if (i <= 1) return 1;
    else return factorial(i-1) * i;
}

int main()
{
    task_pool pool;
    std::future<int> f1 = pool.push(factorial, 30);
}
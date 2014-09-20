#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>


void log(int line)
{
    static std::mutex m;
    std::lock_guard<std::mutex> l(m);
    std::cout << line << std::endl;
}


#define LOG() log(__LINE__)



struct Task
{
    template<typename F>
    Task(F&& f) : f(std::forward<F>(f)) {}
    
    // movable
    Task(Task&& rhs) noexcept : f(std::move(rhs.f)) { }
    Task& operator=(Task&&) noexcept = default;
    
    // non-copyable
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    
    
    void operator()() const
    {
        f();
    }
    
private:
    std::function<void()> f;
};


struct Thread
{
    template<typename ...Args>
    Thread(Args&& ...args) :
        mThread(std::forward<Args>(args)...)
    {
    }
    
    // default movable
    Thread(Thread&&) noexcept = default;
    Thread& operator=(Thread&&) noexcept = default;
    
    // non-copyable
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    
    ~Thread()
    {
        if (mThread.joinable())
        {
            mThread.join();
        }
    }
    
private:
    std::thread mThread;
};

struct Worker
{
    Worker() :
        mThread([=]{ run_thread(); })
    {
        LOG();
    }
    
    Worker(Worker&&) noexcept = default;
    Worker& operator=(Worker&&) noexcept = default; 
    
    Worker(const Worker&) = delete;
    Worker& operator=(const Worker&) = delete;
    
    ~Worker()
    {
        LOG();
        std::unique_lock<std::mutex> lock(mMutex);
        LOG();
        mTasks.clear();
        LOG();
        mTasks.push_back([]{ throw QuitException(); });
        LOG();
        mCondition.notify_all();
        LOG();
        mCondition.wait(lock);
        LOG();
    }
    
    void push_back(Task&& task)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mCondition.notify_all();
        mTasks.push_back(std::move(task));
    }
    
    
    
private:
    struct QuitException {};
    void run_thread()
    {
        try
        {
            run_thread_();
        }
        catch (QuitException&)
        {
            LOG();
            mCondition.notify_all();
        }
    }
        
    void run_thread_()
    {
        Tasks tasks;
        for (;;)
        {   
            {
                std::unique_lock<std::mutex> lock(mMutex);
                mCondition.wait(lock);
                if (mTasks.empty())
                {
                    continue;
                }
            }
            
            std::swap(tasks, mTasks);
            
            while (!tasks.empty())
            {
                auto& task = tasks.back();
                tasks.pop_back();
                try
                {
                    task();
                }
                catch (const std::exception& e)
                {
                    LOG();
                }
            }
        }
    }
    
    typedef std::deque<Task> Tasks;
    
    mutable std::mutex mMutex;
    std::condition_variable mCondition;
    Tasks mTasks;
    Thread mThread;
};


int main()
{
    Worker worker;
}
#include "tbb/concurrent_queue.h"
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <iostream>
#include <string>
#include <thread>
#include <utility>


template<typename T> struct Shared
{
    template<typename ...Args>
    Shared(Args && ...args) :
        mObj(std::forward<Args>(args)...),
        mThread(std::bind(&Shared<T>::consume, this))
    {
    }
    
    struct QuitException : std::runtime_error
    {
        QuitException() : std::runtime_error("QuitException") {}
        ~QuitException() throw() {}
    };
    
    ~Shared()
    {
        execute([](T&) -> int { throw QuitException(); });
        mThread.join();
    }
    
    template<typename F>
    auto execute(F f) -> std::future<typename std::result_of<F(T&)>::type>
    {
        auto promisePtr = std::make_shared<std::promise<typename std::result_of<F(T&)>::type>>();
        mQueue.push(std::bind([=]() -> void {
            try {
                promisePtr->set_value(f(mObj));
            }
            catch (const QuitException&) {
                throw;
            }
            catch (...) {
                promisePtr->set_exception(std::current_exception());
            }
        }));
        return promisePtr->get_future();
    }

private:
    Shared(const Shared&) = delete;
    Shared& operator=(const Shared&) = delete;
    
    typedef std::function<void()> Task;    

    void consume()
    {
        try
        {
            while (true)
            {
                Task task;
                mQueue.pop(task);
                task();
            }
        }
        catch (const QuitException &)
        {
            std::cout << "consume: exiting loop." << std::endl;
        }
    }

    tbb::concurrent_bounded_queue<Task> mQueue;
    T mObj;
    std::thread mThread;
};

template<> struct Shared<void>
{
    Shared() :
        mThread(std::bind(&Shared<void>::consume, this))
    {
    }
    
    struct QuitException : std::runtime_error
    {
        QuitException() : std::runtime_error("QuitException") {}
        ~QuitException() throw() {}
    };
    
    ~Shared()
    {
        execute([]() -> int { throw QuitException(); });
        mThread.join();
    }
    
    template<typename F>
    auto execute(F f) -> std::future<void>
    {
        auto promisePtr = std::make_shared<std::promise<void>>();
        mQueue.push(std::bind([=]() -> void {
            try {
                f();
                promisePtr->set_value();
            }
            catch (const QuitException&) {
                throw;
            }
            catch (...) {
                promisePtr->set_exception(std::current_exception());
            }
        }));
        return promisePtr->get_future();
    }

private:
    Shared(const Shared&) = delete;
    Shared& operator=(const Shared&) = delete;
    
    typedef std::function<void()> Task;    

    void consume()
    {
        try
        {
            while (true)
            {
                Task task;
                mQueue.pop(task);
                task();
            }
        }
        catch (const QuitException &)
        {
            std::cout << "consume: exiting loop." << std::endl;
        }
    }

    tbb::concurrent_bounded_queue<Task> mQueue;
    std::thread mThread;
};


template<typename SchedulerPolicy>
struct BasicStack : SchedulerPolicy
{ 
    // Use this for threaded access to the stack.
    template<typename F>
    void post(const F& f)
    {
        SchedulerPolicy::do_post(f);
    }
    
    void setIP(const std::string&) {}
};


struct TBBScheduler : private Shared<void>
{   
    template<typename F>
    void do_post(const F& f)
    {
        this->execute(f);
    }
};

int main()
{
    typedef BasicStack<TBBScheduler> Stack;
    Stack stack;
    stack.post([&stack]{ stack.setIP(""); });
}

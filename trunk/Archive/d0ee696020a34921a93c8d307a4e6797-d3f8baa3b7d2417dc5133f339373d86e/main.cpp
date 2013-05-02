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
#include <vector>


template<typename T>
struct Shared
{
    template<typename ...Args>
    Shared(Args && ...args) :
        mObj(std::forward<Args>(args)...),
        mThread()
    {
    }
    
    struct QuitException : std::runtime_error
    {
        QuitException() : std::runtime_error("QuitException") {}
        ~QuitException() throw() {}
    };
    
    ~Shared()
    {
        if (mThread)
        {
            execute([](T&) -> int { throw QuitException(); });
            mThread->join();
        }
    }
    
    template<typename F>
    auto execute(F f) -> std::future<typename std::result_of<F(T&)>::type>
    {
        // lazy initialize thread
        if (!mThread)
        {
            mThread.reset(new std::thread(std::bind(&Shared<T>::consume, this)));
        }
        
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
    std::unique_ptr<std::thread> mThread;
};


// Specialization for 'void' does not operate on object.
// This works similar to std::async.
template<>
struct Shared<void>
{
    Shared()
    {
    }
    
    struct QuitException : std::runtime_error
    {
        QuitException() : std::runtime_error("QuitException") {}
        ~QuitException() throw() {}
    };
    
    ~Shared()
    {
        if (mThread)
        {
            execute([]() -> int { throw QuitException(); });
            mThread->join();
        }
    }
    
    template<typename F>
    auto execute(F f) -> std::future<void>
    {
        if (!mThread)
        {
            mThread.reset(new std::thread(std::bind(&Shared<void>::consume, this)));
        }
        
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
    std::unique_ptr<std::thread> mThread;
};

struct WorkerPool
{
    typedef std::function<void()> Task;    
    WorkerPool(std::size_t size = 1) :
        mQuit(false),
        mWorkers(size)
    {
        for (auto& worker : mWorkers)
        {
            worker.execute([this, &worker]() {
                std::unique_lock<std::mutex> lock(mDestructorMutex);
                if (mQuit)
                {
                    return;
                }
                Task task;
                mQueue.pop(task);
                return worker.execute(task);
            });
        }
    }
    
    ~WorkerPool()
    {        
        std::unique_lock<std::mutex> lock(mDestructorMutex);
        mQuit = true;
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
            catch (const Shared<void>::QuitException&) {
                throw;
            }
            catch (...) {
                promisePtr->set_exception(std::current_exception());
            }
        }));
    }
     
    std::atomic<bool> mQuit;
    std::mutex mDestructorMutex;
    tbb::concurrent_bounded_queue<Task> mQueue;
    std::vector<Shared<void>> mWorkers;
};

int main()
{
    WorkerPool pool(2);
    pool.execute([]{std::cout << __COUNTER__ << std::endl;});
    pool.execute([]{std::cout << __COUNTER__ << std::endl;});
    pool.execute([]{std::cout << __COUNTER__ << std::endl;});
    pool.execute([]{std::cout << __COUNTER__ << std::endl;});
}

#include "tbb/concurrent_queue.h"
#include <chrono>
#include <condition_variable>
#include <deque>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_set>
#include <utility>
#include <vector>


template<typename T>
struct Shared
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


// Specialization for 'void' does not operate on object.
// This works similar to std::async.
template<>
struct Shared<void>
{
    Shared() : mThread(std::bind(&Shared<void>::consume, this))
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

using Worker = Shared<void>;

template<typename T>
void print(const T &t)
{
    static std::mutex fMutex;
    std::lock_guard<std::mutex> lock(fMutex);
    std::cout << t << std::endl;
}

// Work-stealing 
struct WorkerPool
{
    typedef std::function<void()> Task;
        
    WorkerPool(std::size_t inSize = 1) : mQuit(false), mWorkers(inSize)
    {        
        for (auto& worker : mWorkers)
        {
            worker.execute([this]{                
                std::unique_lock<std::mutex> lock(mMutex);
                while (!mQuit) {
                    while (!mQueue.empty()) {
                        Task task = mQueue.front();
                        mQueue.pop_front();
                        task();
                    }
                    mCondition.wait(lock);
                }
            });
        }
    }
    
    ~WorkerPool()
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mQuit = true;
        mCondition.notify_all();
    }
    
    template<typename F>
    auto execute(F f) -> std::future<void>
    {        
        std::unique_lock<std::mutex> lock(mMutex);
        auto prom = std::make_shared<std::promise<void>>();
        mQueue.push_back([=]{
            try {
                f();
                prom->set_value();
            } catch (...) {
                prom->set_exception(std::current_exception());
            }
        });
        mCondition.notify_all();
        return prom->get_future();
    }
    
    std::mutex mMutex;
    std::condition_variable mCondition;
    std::deque<Task> mQueue;
    std::atomic<bool> mQuit;
    std::vector<Worker> mWorkers;
};


int main()
{
    print("begin");
    {
        WorkerPool pool{4};
        std::vector<std::future<void>> futures;
        for (int i = 0; i != 16; ++i)
            futures.emplace_back(pool.execute([=]{print(i);}));
        
        std::unordered_set<std::future<void>*> already_ok;
        for (;;)
        {
            for (auto& fut : futures)
            {
                if (already_ok.count(&fut))
                {
                    continue;
                }
                if (std::future_status::ready == fut.wait_for(std::chrono::milliseconds(0)))
                {
                    already_ok.insert(&fut);
                }
                else
                {
                    std::this_thread::yield();
                }
            }
            
            if (already_ok.size() == futures.size())
            {
                break;
            }
        }
    }
    print("end");
}

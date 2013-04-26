#include "tbb/concurrent_queue.h"
#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <iostream>
#include <thread>
#include <utility>


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

struct Car
{
    unsigned increment_age() { return ++age_; }
    unsigned age() const { return age_; }
    
    int age_ = 0;
};

int main()
{
    Shared<Car> a;
    auto age1 = a.execute([](Car & c) { return c.increment_age(); });
    auto age2 = a.execute([](Car & c) { return c.increment_age(); });
    auto age3 = a.execute([](Car & c) { return c.increment_age(); });
    std::cout << age1.get() << ", " << age2.get() << ", " << age3.get() << std::endl;
    
    
    // Shard<void> works similar to std::async.
    Shared<void> worker;
     worker.execute([]() { std::cout << __LINE__ << std::endl; });
    worker.execute([]() { std::cout << __LINE__ << std::endl; });
    auto f3 = worker.execute([]() { std::cout << __LINE__ << std::endl; });
    std::cout << "Wait for results..." << std::endl;
    f3.wait(); // must be called (which would not be the case with std::async)
}

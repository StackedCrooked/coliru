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
        std::promise<typename std::result_of<F(T&)>::type> p;
        mQueue.push(std::bind([&]() -> void {
            try {
                p.set_value(f(this->mObj));
            }
            catch (const QuitException&) {
                throw;
            }
            catch (...) {
                p.set_exception(std::current_exception());
            }
        }));
        return p.get_future();
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
}

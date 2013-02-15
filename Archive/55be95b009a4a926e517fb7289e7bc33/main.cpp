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

    ~Shared()
    {
        struct QuitException : std::runtime_error
        {
            QuitException() : std::runtime_error("QuitException") {}
            ~QuitException() throw() {}
        };
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
            } catch (...) {
                promisePtr->set_exception(std::current_exception());
            }
        }));
        return promisePtr->get_future();
    }

private:
    Shared(const Shared&) = delete;
    Shared& operator=(const Shared&) = delete;
    
    typedef std::function<void()> Task; // type erased in order to allow various types of tasks

    void consume()
    {
        while (true)
        {
            Task task;
            mQueue.pop(task);
            task();
        }
    }

    tbb::concurrent_bounded_queue<Task> mQueue; // lockless queue would be better
    T mObj;
    std::thread mThread;
};

struct Car
{
    unsigned age() const { return 777; }
    unsigned weight() const { return 888; }
};

int main()
{
    std::cout << "a 0" << std::endl;
    Shared<Car> a,b,c;    
    std::cout << "a 1" << std::endl;
    auto age_a = a.execute([](Car & c) -> unsigned { return c.age(); });
    std::cout << "a 2" << std::endl;
    auto age_b = b.execute([](Car & c) -> unsigned { return c.age(); });
    std::cout << "a 3" << std::endl;
    auto age_c = c.execute([](Car & c) -> unsigned { return c.age(); });
    std::cout << "a 4" << std::endl;
    std::cout << age_a.get() << std::endl;
    std::cout << "a 5" << std::endl;
    std::cout << age_b.get() << std::endl;
    std::cout << "a 6" << std::endl;
    std::cout << age_c.get() << std::endl;
    std::cout << "a 7" << std::endl;
}

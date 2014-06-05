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
struct Shared {
    template<typename ...Args>
    Shared(Args && ...args) :
        obj_(std::forward<Args>(args)...),
        thread_(std::bind(&Shared<T>::consume, this))
    {
    }
    
    struct QuitException : std::runtime_error {
        QuitException() : std::runtime_error("QuitException") {}
        ~QuitException() throw() {}
    };
    
    ~Shared() {
        dispatch([](T&) -> int { throw QuitException(); });
        thread_.join();
    }
    
    template<typename F>
    auto dispatch(F f) -> std::future<decltype(f(std::declval<T>()))>
    {
        typedef decltype(f(obj_)) R;
        
        auto promisePtr = std::make_shared<std::promise<R>>();
        
        mQueue.push([=] {
            try { promisePtr->set_value(f(obj_)); }
            catch (const QuitException&) { throw; }
            catch (...) { promisePtr->set_exception(std::current_exception()); }
        });
        return promisePtr->get_future();
    }

private:
    Shared(const Shared&) = delete;
    Shared& operator=(const Shared&) = delete;
    
    typedef std::function<void()> Task;    

    void consume()
    {
        try {
            for (;;) {
                Task task;
                mQueue.pop(task);
                task();
            }
        }
        catch (const QuitException &) {
            std::cout << "consume: exiting loop." << std::endl;
        }
    }

    tbb::concurrent_bounded_queue<Task> mQueue;
    T obj_;
    std::thread thread_;
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
    auto age1 = a.dispatch([](Car & c) { return c.increment_age(); });
    auto age2 = a.dispatch([](Car & c) { return c.increment_age(); });
    auto age3 = a.dispatch([](Car & c) { return c.increment_age(); });
    std::cout << age1.get() << ", " << age2.get() << ", " << age3.get() << std::endl;
}

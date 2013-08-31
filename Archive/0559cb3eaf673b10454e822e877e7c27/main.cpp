#include "tbb/concurrent_queue.h"
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

template<typename T>
struct Shared
{
    template<typename ...Args>
    Shared(Args && ...args) :
        mObj(std::forward<Args>(args)...),
        mThread([this]{ consume(); })
    {
    }

    ~Shared()
    {
        mQueue.push([this]{ mStop = true; });
        mThread.join();
    }
    
    template<typename F, typename R = typename std::result_of<F(T&)>::type>
    std::future<R> execute(F f)
    {
        std::packaged_task<R()> task([=]{ return f(mObj); });
        auto future = task.get_future();
        //mQueue.push(std::move(task));
        return future;
    }

private:
    Shared(const Shared&) = delete;
    void operator=(const Shared&) = delete;
    
    void consume()
    {
        while (!mStop)
        {
            std::function<void()> f;
            mQueue.pop(f);
            f();
        }
    }

    bool mStop = false;
    tbb::concurrent_bounded_queue<std::function<void()>> mQueue;
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
    a.execute([](Car & c) { return c.increment_age(); });
    //auto age1 = a.execute([](Car & c) { return c.increment_age(); });
    //auto age2 = a.execute([](Car & c) { return c.increment_age(); });
    //auto age3 = a.execute([](Car & c) { return c.increment_age(); });
    //std::cout << age1.get() << ", " << age2.get() << ", " << age3.get() << std::endl;
}

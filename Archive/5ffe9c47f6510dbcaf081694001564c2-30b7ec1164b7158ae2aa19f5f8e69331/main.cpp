#include "tbb/concurrent_queue.h"
#include <future>
#include <iostream>
#include <thread>
#include <unistd.h>


namespace ThreadSupport {


//
// Helper functions
//
template<typename F>
auto MakeSharedPromise(F f) -> std::shared_ptr<std::promise<decltype(f())>>
{
    return std::make_shared<std::promise<decltype(f())>>();
}


template<typename R, typename F>
void SetPromise(std::promise<R>& p, F f)
{
    p.set_value(f());
}


template<typename F>
void SetPromise(std::promise<void>& p, F f)
{
    f();
    p.set_value();
}


template<typename F, typename ...Args>
auto Async(F f, Args&& ...args) -> std::future<decltype(f(std::declval<Args>()...))>
{
    typedef decltype(f(std::declval<Args>()...)) R;
    auto task = std::packaged_task<R(Args...)>(f);
    std::future<R> future = task.get_future();
    std::thread(std::move(task), std::forward<Args>(args)...).detach();
    return future;
}


//
// Scheduler
//
struct Scheduler
{
    Scheduler() : mLifetime(nullptr, [](void*){})
    {
        auto checker = get_checker();
        Async([=]{
            try {
                while (!checker.expired()) {
                    std::function<void()> f;
                    concurrent_queue.pop(f);
                    f();
                }
            } catch (QuitException) {
                // exit the thread.
            }
        });
    }

    Scheduler(const Scheduler&) = delete;
    Scheduler& operator=(const Scheduler&) = delete;


    ~Scheduler()
    {
        dispatch([=]{
            throw QuitException{};
        }).wait();
    }

    template<typename F>
    auto dispatch(F f) -> std::future<decltype(f())>
    {
        auto p = MakeSharedPromise(f);
        concurrent_queue.push([=]{
            SetPromise(*p, f);
        });
        return p->get_future();
    }

    template<typename F>
    auto schedule(F f, int timeout) -> decltype(Async(f))
    {
        auto checker = get_checker();
        auto absolute_time = Clock::now() + std::chrono::milliseconds(timeout);
        return Async([=] { this->do_schedule(f, absolute_time, checker); });
    }

private:
    typedef std::chrono::system_clock Clock;
    
    struct QuitException {};
    
    template<typename F>
    auto do_schedule(F f, Clock::time_point absolute_time, std::weak_ptr<void> lifetime_checker) -> decltype(Async(f))
    {
        typedef std::chrono::system_clock Clock;
        while (Clock::now() < absolute_time) {
            usleep(500000);
            if (lifetime_checker.expired()) {
                throw std::runtime_error("cancelled");
            }
        }
        return dispatch(f);
    }

    std::weak_ptr<void> get_checker() const
    {
        return mLifetime;
    }

    tbb::concurrent_bounded_queue<std::function<void()>> concurrent_queue;
    std::shared_ptr<void> mLifetime;
};


} // namespace TreadSupport



#include <iostream>


void run()
{
    using ThreadSupport::Scheduler;
    
    std::cout << "Begin!" << std::endl;

    // create scheduler on the stack
    Scheduler s;
    
    // schedule a number of taskes with timeouts
    for (int i = 1; i != 20; ++i)
    {
        try {
            s.schedule([=]{ std::cout << "ms: " << (i*i) << std::endl; }, (i*i));
        }
        catch (std::system_error& e) {
            std::string msg = e.what();
            s.dispatch([=,&s]{std::cout << "ms " << (i*i) << " failed because: " << msg << " (This is Coliru! Let's wait a little.)" << std::endl;});
            usleep(i*i);
        }
    }
    
    // sleep for one second to allow some of the tasks to run
    sleep(1);
    
    // End of scope => Scheduler will be destroyed => scheduled threads are cancelled!
    std::cout << "End of scope!" << std::endl;
}


int main()
{
    run();
}
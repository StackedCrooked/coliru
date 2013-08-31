#include "tbb/concurrent_queue.h"
#include <future>
#include <iostream>
#include <deque>
#include <thread>
#include <unistd.h>


namespace {


//
// Helper functions
//
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


// Returns a future that doesn't block in its destructor.
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
struct Scheduler : std::enable_shared_from_this<Scheduler>
{
    static std::shared_ptr<Scheduler> Create()
    {
        return std::make_shared<Scheduler>(Private{});
    }
    
    // Make the constructor private while still being public.
    // (Public constructor is required for std::make_shared).
    class Private
    {
        friend class Scheduler;
        Private() {}
    };
    
    Scheduler(Private)
    {
        Async([=]
        {
            try
            {
                while (true)
                {
                    std::function<void()> f;
                    concurrent_queue.pop(f);
                    f();
                }
            }
            catch (QuitException)
            {
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
        auto p = std::make_shared<std::promise<decltype(f())>>();
        concurrent_queue.push([=]{
            SetPromise(*p, f);
        });
        return p->get_future();
    }

    template<typename F>
    auto schedule(F f, int timeout) -> decltype(Async(f))
    {
        auto absolute_time = Clock::now() + std::chrono::milliseconds(timeout);
        auto shared = this->shared_from_this();
        return Async([=] { this->do_schedule(f, absolute_time, shared); });
    }

private:
    struct QuitException {};
    typedef std::chrono::system_clock Clock;
    
    
    template<typename F>
    auto do_schedule(F f, Clock::time_point absolute_time, std::weak_ptr<Scheduler> weak_scheduler) -> decltype(Async(f))
    {
        if (std::shared_ptr<Scheduler> shared{weak_scheduler})
        {
            typedef std::chrono::system_clock Clock;
            while (Clock::now() < absolute_time) {
                usleep(50);
            }
            return dispatch(f);
        }
        else
        {
            throw std::runtime_error("Expired!");
        }
    }

    tbb::concurrent_bounded_queue<std::function<void()>> concurrent_queue;
};


} // namespace TreadSupport



#include <iostream>


int main()
{
    auto s = Scheduler::Create();
    std::deque<std::future<void>> futures;
    for (auto i = 0ul; i != 100; ++i)
    {
        try
        {
            auto ms = rand()%100;
            futures.emplace_back(s->schedule([=]{
                std::cout << i << ": " << ms << std::endl;
            }, ms));
        }
        catch (std::system_error& e)
        {
            std::string msg = e.what();
            s->dispatch([=] { puts(msg.c_str()); });
            while (!futures.empty())
            {
                futures.back().wait();
                futures.pop_back();
            }
        }
    }
    futures.back().wait();
}

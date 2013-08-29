#include "tbb/concurrent_queue.h"
#include <future>
#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>


namespace ThreadSupport {


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
struct Scheduler
{
    Scheduler()
    {
        Async([=]{
            try {
                while (true) {
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
        return Async([=] { this->do_schedule(f, absolute_time); });
    }

private:
    typedef std::chrono::system_clock Clock;
    
    struct QuitException {};
    
    template<typename F>
    auto do_schedule(F f, Clock::time_point absolute_time) -> decltype(Async(f))
    {
        typedef std::chrono::system_clock Clock;
        while (Clock::now() < absolute_time) {
            usleep(500000);
        }
        return dispatch(f);
    }

    tbb::concurrent_bounded_queue<std::function<void()>> concurrent_queue;
};


} // namespace TreadSupport



#include <iostream>


void run()
{
    using ThreadSupport::Scheduler;
    
    std::cout << "Begin!" << std::endl;

    // create scheduler on the stack
    Scheduler s;
    
    
    std::vector<std::future<void>> futures;
    
    // schedule a number of taskes with timeouts
    for (int i = 1; i != 33; ++i)
    {
        int ms = i*i;
        try {
            futures.push_back(s.schedule([=]{ std::cout << "ms: " << ms << std::endl; }, ms));
        }
        catch (std::system_error& e) {
            std::string msg = e.what();
            s.dispatch([=,&s]{std::cout << "Scheduling task " << i << " of " << ms << " ms failed because: " << msg << " (This is Coliru! Let's wait a little.)" << std::endl;});
            if (!futures.empty())
            {
                futures.back().wait();
                futures.pop_back();
            }
        }
    }
    
    
    std::cout << "End of scope reached. Joining..." << std::endl;
}


int main()
{
    run();
}
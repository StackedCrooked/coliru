#include "tbb/concurrent_queue.h"
#include <future>
#include <mutex>
#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>


namespace {
    
    
void print(std::string s)
{
    static std::mutex fMutex;
    std::lock_guard<std::mutex> lock(fMutex);
    std::cout << s << std::endl;
}


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
                for (;;) {
                    std::function<void()> f;
                    concurrent_queue.pop(f);
                    f();
                }
            } catch (QuitException) {
                throw;
            }
        });
    }

    Scheduler(const Scheduler&) = delete;
    Scheduler& operator=(const Scheduler&) = delete;


    ~Scheduler()
    {
        try
        {
            print("Posting the QuitException");
            dispatch([=]{ throw QuitException{}; }).get();
        }
        catch (QuitException)
        {
            print("Caught QuitException");
        }
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
        while (absolute_time - Clock::now() > std::chrono::microseconds(50)) {
            usleep(100);
        }
        return dispatch(f);
    }

    tbb::concurrent_bounded_queue<std::function<void()>> concurrent_queue;
};


} // namespace



#include <iostream>


void run()
{
    using namespace std::chrono;

    // create scheduler on the stack
    Scheduler s;
    
    
    std::vector<std::future<void>> futures;
    
    
    // schedule a number of taskes with timeouts
    for (int i = 1; i != 100; ++i)
    {
        int ms = 3 * i / 2;
        try {
            auto begin_time = system_clock::now();
            auto future = s.schedule([=]() -> void {
                auto actual_timeout = duration_cast<milliseconds>(system_clock::now() - begin_time);
                print("Task=" + std::to_string(i) + " scheduled_timeout=" + std::to_string(ms) + ", actual_timeout=" + std::to_string(actual_timeout.count()) + " ms");
            }, ms);
            futures.push_back(std::move(future));
        } catch (std::system_error& e) {
            std::string msg = e.what();
            print("Creating thread for task " + std::to_string(i) + " failed: " + msg + ". (Coliru process limit exceeded. Joining all current tasks before proceeding.)");
            while (!futures.empty())
            {
                futures.back().wait();
                futures.pop_back();
            }
        }
    }
    
    
    print("End of scope reached. Joining...");
}


int main()
{
    run();
}
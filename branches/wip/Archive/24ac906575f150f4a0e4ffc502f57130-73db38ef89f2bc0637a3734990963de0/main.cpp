#include "tbb/concurrent_queue.h"
#include <future>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unistd.h>


std::atomic<unsigned> exception_counter{0};

struct Stack
{
    Stack() :
        mThread([=]{
            try {
                for (;;) {
                    std::function<void()> f;
                    this->q.pop(f);
                    f();
                }
            } catch (int) {
                std::cout << "Stopping the thread!" << std::endl;
            }
        }),
        mCheckLifetime(this, [](Stack*){})
    {
    }

    ~Stack()
    {
        mCheckLifetime.reset();
        q.push([]{throw 1;});
        mThread.join();
    }

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    template<typename F>
    auto dispatch(F f) -> std::future<decltype(f())>
    {
        auto p = make_shared_promise(f);
        q.push([=]{
            set_promise(*p, f);
        });
        return p->get_future();
    }

    template<typename F>
    auto schedule(F f, unsigned ms) -> std::future<decltype(f())>
    {
        return do_schedule(f, ms, 0);
    }

private:
    template<typename F>
    auto do_schedule(F f, unsigned ms, unsigned wait) -> std::future<decltype(f())>
    {
        if (wait > 0)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(wait));
        }
        else
        {
            wait = 1;
        }

        try
        {
            // start thread
            auto p = make_shared_promise(f);
            std::weak_ptr<Stack> checklifetime = mCheckLifetime;
            std::thread([=]{
                usleep(1000 * ms);
                if (checklifetime.expired()) {
                    return;
                }
                this->set_promise(*p, [=]{ return dispatch(f).get(); });
            }).detach();
            return p->get_future();
        }
        catch (std::system_error& e)
        {
            exception_counter++;
            return do_schedule(f, ms, wait * 2);
        }
    }

    template<typename R, typename F>
    void set_promise(std::promise<R>& p, F f)
    {
        p.set_value(f());
    }

    template<typename F>
    void set_promise(std::promise<void>& p, F f)
    {
        f();
        p.set_value();
    }

    template<typename T>
    using SharedPromise = std::shared_ptr<std::promise<T>>;

    template<typename F>
    auto make_shared_promise(F f) -> SharedPromise<decltype(f())>
    {
        return std::make_shared<std::promise<decltype(f())>>();
    }

    tbb::concurrent_bounded_queue<std::function<void()>> q;
    std::thread mThread;
    std::shared_ptr<Stack> mCheckLifetime;
};


int main()
{
    Stack s;
    s.dispatch([]{});


    std::vector<std::future<int>> futures;
    futures.reserve(10);
    for (auto i = 0UL; i != futures.capacity(); ++i)
    {
        auto t = rand()%50;
        futures.emplace_back(
                    s.schedule([=]() -> int { return t; }, t)
        );
    }


    [&]{
        std::cout << "Index\tDuration" << std::endl;
        std::unordered_set<void*> ok;
        for (;;)
        {
            for (auto& f : futures)
            {
                if (0u == ok.count(&f) && std::future_status::ready == f.wait_for(std::chrono::microseconds(0)))
                {
                    std::cout << (&f - &*futures.begin()) << '\t' << f.get() << std::endl;
                    ok.insert(&f);
                    if (ok.size() == futures.size())
                    {
                        return;
                    }
                }
            }
        }
    }();

    std::cout << std::endl << "exception_counter: " << exception_counter << std::endl;
}


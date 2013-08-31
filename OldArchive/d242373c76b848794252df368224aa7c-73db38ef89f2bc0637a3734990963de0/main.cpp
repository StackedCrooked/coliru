#include "tbb/concurrent_queue.h"
#include <future>
#include <iostream>
#include <unistd.h>
    
template<typename T>
using SharedPromise = std::shared_ptr<std::promise<T>>;

template<typename F>
auto make_shared_promise(F f) -> SharedPromise<decltype(f())>
{
    return std::make_shared<std::promise<decltype(f())>>();
}

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

    tbb::concurrent_bounded_queue<std::function<void()>> q;
    std::thread mThread;
    std::shared_ptr<Stack> mCheckLifetime;
};


int main()
{
    std::cout << __VERSION__ << std::endl;
    std::thread([]{ sleep(1); std::cout << "Timeout!" << std::endl; std::abort(); }).detach();
    Stack s;
    s.dispatch([]{});

    std::cout << s.dispatch([] { return "Hello dispatch!"; }).get() << std::endl;

    s.schedule([] { std::cout << "1ms" << std::endl; }, 1);
    s.schedule([] { std::cout << "2ms" << std::endl; }, 2);
    s.schedule([] { std::cout << "3ms" << std::endl; }, 3);
    s.schedule([] { std::cout << "4ms" << std::endl; }, 4);
    s.schedule([] { std::cout << "5ms" << std::endl; }, 5);
    usleep(2000);
}


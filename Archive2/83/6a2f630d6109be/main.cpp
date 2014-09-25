// Copyright Evgeny Panasyuk 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// e-mail: E?????[dot]P???????[at]gmail.???

// Full emulation of await feature from C# language in C++ based on Stackful Coroutines from
// Boost.Coroutine library.
// This proof-of-concept shows that exact syntax of await feature can be emulated with help of
// Stackful Coroutines, demonstrating that it is superior mechanism.
// Main aim of this proof-of-concept is to draw attention to Stackful Coroutines.

// https://github.com/panaseleus/await_emu
// http://rsdn.ru/forum/cpp/5219587.flat

// GOTO entry_point

#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#define BOOST_THREAD_PROVIDES_FUTURE

#include <boost/coroutine/all.hpp>
#include <boost/optional.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>

#include <initializer_list>
#include <functional>
#include <iostream>
#include <cstddef>
#include <utility>
#include <cstdlib>
#include <memory>
#include <vector>
#include <stack>
#include <queue>
#include <ctime>

using namespace std;
using namespace boost;

// ___________________________________________________________ //
template<typename T>
class concurrent_queue
{
    queue<T> q;
    boost::mutex m;
    boost::condition_variable c;
public:
    template<typename U>
    void push(U &&u)
    {
        auto &&l = make_lock_guard(m);
        q.push( forward<U>(u) );
        c.notify_one();
    }
    void pop(T &result)
    {
        boost::unique_lock<boost::mutex> u(m);
        c.wait(u, [&]{return !q.empty();} );
        result = move_if_noexcept(q.front());
        q.pop();
    }
};
// ___________________________________________________________ //
template<typename F>
class Worker
{
    using Job = boost::optional<F>;
    concurrent_queue<Job> q;
    boost::thread worker;
public:
    Worker()  : worker{[this]
                {
                    Job j;
                    while(true)
                    {
                        q.pop(j);
                        if(!j) break;
                        (*j)();
                    }
                }}
    {}
    void finish()
    {
        q.push(Job{});
    }
    void operator()(F &&f)
    {
        q.push(Job{std::move(f)});
    }
    ~Worker()
    {
        worker.join();
    }
    Worker(Worker&&)=delete;
    Worker &operator=(Worker&&)=delete;
};
// ___________________________________________________________ //
using Task = std::function<void()>;
using TaskQueue = Worker<Task>;

using Context = TaskQueue*;
Context default_context{};
Context main_context{};
Context worker_context{};

template<typename F>
auto post_task(Context context, F f)
{
    // same rationale as in asynchronous
    auto result_promise = make_shared<promise<decltype(f())>>(); 
    auto result_future = result_promise->get_future();

    (*context)([result_promise=std::move(result_promise), f=std::move(f)]() mutable
    {
        result_promise->set_value( f() );
    });
    return result_future;
}
// ___________________________________________________________ //
using coro_pull = coroutines::symmetric_coroutine<void>::call_type;
using coro_push = coroutines::symmetric_coroutine<void>::yield_type;

struct CurrentCoro
{
    std::shared_ptr<coro_pull> resume;
    unsigned id;
    TaskQueue *context;
    coro_push *yield;
};

thread_local stack<CurrentCoro> coro_stack;
atomic<unsigned> total_coro_counter;

void switch_context_to(Context context)
{
    coro_stack.top().context = context;
}
// ___________________________________________________________ //
template<typename F>
auto asynchronous(F f)
{
    promise<decltype(f())> coro_promise;
    auto coro_future = coro_promise.get_future();

    // It is possible to avoid shared_ptr and use move-semantic,
    //     but it would require to refuse use of std::function (it requires CopyConstructable),
    //     and would lead to further complication and is unjustified
    //     for purposes of this proof-of-concept
    CurrentCoro current_coro =
    {
        make_shared<coro_pull>([f, coro_promise=std::move(coro_promise)](auto &caller) mutable
        {
            coro_stack.top().yield = &caller;
            coro_promise.set_value( f() );
        }),
        total_coro_counter++,
        default_context
    };

    coro_stack.push( std::move(current_coro) );
    (*coro_stack.top().resume)();
    coro_stack.pop();

    return coro_future;
}

struct Awaiter
{
    template<typename Future>
    auto operator*(Future &&ft) const
    {
        auto &&current_coro = coro_stack.top();
        auto result = ft.then([current_coro](auto ready_future)
        {
            (*current_coro.context)([current_coro]
            {
                coro_stack.push(std::move(current_coro));
                (*coro_stack.top().resume)();
                coro_stack.pop();
            });
            return ready_future.get();
        });
        (*coro_stack.top().yield)();
        return result.get();
    }
};

#define ASYNC_PREFIX(func) \
template<typename ...Args> \
auto async_##func(Args... args) \
{ \
    return asynchronous([=]() mutable \
    { \
        return func(args...); \
    }); \
} \
/**/

#define await Awaiter()*
// ___________________________________________________________ //
void entry_point();

int main()
{
    srand(time(0));

    // Custom scheduling is not required - can be integrated
    // to other systems transparently
    TaskQueue main_tasks, worker_tasks;

    default_context = &main_tasks;
    main_context = &main_tasks;
    worker_context = &worker_tasks;

    main_tasks([&]{asynchronous([&]
    {
        entry_point();

        main_tasks.finish();
        worker_tasks.finish();
        return true;
    });});
}
// __________________________________________________________________ //
template<typename ...Args>
void print(Args... args)
{   
    static boost::mutex m;
    auto &&l = make_lock_guard(m);

    cout << "Thread ID=" << this_thread::get_id();
    if(!coro_stack.empty())
        cout << " Coro ID=" << coro_stack.top().id;
    else
        cout << " Non-Coro";
    cout << ":\t";
    initializer_list<bool>{((cout << args), true)...};
    cout << endl;
}

void reschedule()
{
    boost::this_thread::sleep_for(boost::chrono::milliseconds( rand() % 2000 ));
}

auto some_async_operation()
{
    return async([]{ return reschedule(), 1; });
}
// __________________________________________________________________ //
// __________________________________________________________________ //
// __________________________________________________________________ //
int bar(int i)
{
    print("bar{A}, arg=", i);
    
    if(i/10 % 2 == 1)
        switch_context_to(worker_context);

    // await is not limited by "one level" as in C#    
    auto result = await post_task(worker_context, [i]
    {
        print("inside task, arg=", i);
        return (i+1)*(i+2);
    });

    print("bar{B}");
    return result;
}

int foo(int i)
{
    print("foo{A}, arg=", i);
    await some_async_operation();
    print("foo{B}");
    auto result = bar(i);
    print("foo{C}");
    return result;
}
ASYNC_PREFIX(foo)

void entry_point()
{
    constexpr auto N = 8;
    print("entry_point{A}");

    vector<future<int>> fs;
    for(auto i=0; i!=N; ++i)
    {
        fs.push_back( async_foo((i+1)*10) );
        // Alternative:
        //  fs.push_back( asynchronous([i]{ return foo((i+1)*10); }) );
    }

    print("entry_point{B}");
    for(auto &&f : fs)
        print("Result=", await f);
    print("entry_point{C}");
}


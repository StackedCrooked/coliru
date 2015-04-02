#include <iostream>
#include <functional>
#include <future>

void runSometime(std::function<void()> fn) {
    // ... enqueue to run in some other thread sometime
}

template<typename F>
auto sync(F fn) -> std::future<decltype(fn())>
{
    typedef std::promise<decltype(fn())> PromiseType;
    typedef std::future<decltype(fn())> FutureType;

    // Using functor so I can move
    struct lambda
    {
        PromiseType result;
        F fn;

        lambda(F fn, FutureType& future)
            : fn(std::move(fn))
        {
            future = result.get_future();
        }
        
        lambda(lambda &&r) = default;

        void operator()()
        {
            result.set_value(fn());
        }
    };

    FutureType result;
    runSometime(lambda(std::move(fn), result));
    return result;
}

int main()
{
    auto somePromise = sync([] {
        return 42;
    });
    
    std::cout << somePromise.get();
}

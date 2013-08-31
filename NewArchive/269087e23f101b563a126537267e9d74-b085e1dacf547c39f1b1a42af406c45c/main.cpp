#include <iostream>
#include <future>
#include <type_traits>


template<typename T>
struct Future : std::shared_future<T>
{
    Future(std::shared_future<T> f) :
        std::shared_future<T>(move(f))
    {
    }
    
    template<typename F>
    auto then(F f) -> Future<decltype(f(std::declval<T>()))>
    {
        typedef decltype(f(std::declval<T>())) R;
        return Future<R>(std::move(std::async(std::launch::async, [=]() -> R {
            return f(this->get());
        })));
    }

    template<typename F>
    void finally(F f)
    {
        f(this->get());
    }
};


template<>
struct Future<void> : std::shared_future<void>
{
    Future(std::shared_future<void> f) :
        std::shared_future<void>(move(f))
    {
    }
    
    template<typename F>
    auto then(F f) -> Future<decltype(f())>
    {
        typedef decltype(f()) R;
        return Future<R>(std::async(std::launch::async, [=]() -> R {
            this->wait();
            return f();
        }));
    }

    template<typename F>
    void finally(F f)
    {
        this->wait();
        return f();
    }
};


// takes an lvalue and returns a Future<T&>
template<typename T>
auto take(T& t) -> Future<T&>
{
    T* pt = &t;
    return Future<T&>(move(std::async([=]()-> T& { return (*pt);})));
}


template<typename R, typename F, typename ...Args>
auto Async(F&& f, Args&& ...args) -> Future<R>
{
    return Future<R>(std::async(std::forward<F>(f), std::forward<Args>(args)...));
}


int main()
{
#ifndef COUNT 
#error COUNT undefined.
#endif

#if COUNT == 0
    Async<void>([]{}).finally([]{});
#elif COUNT == 1
    Async<void>([]{}).then([]{}).finally([]{});
#elif COUNT == 2
    Async<void>([]{}).then([]{}).then([]{}).finally([]{});
#elif COUNT == 4
    Async<void>([]{}).then([]{}).then([]{}).then([]{}).then([]{}).finally([]{});
#elif COUNT == 8
    Async<void>([]{}).then([]{}).then([]{}).then([]{}).then([]{}).then([]{}).then([]{}).then([]{}).then([]{}).finally([]{});
#else
#error Invalid value for COUNT.
#endif
        
}

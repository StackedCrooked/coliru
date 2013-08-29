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


template<> template<typename F>
Future<void> Future<void>::finally(F f)
{
    this->wait();
    f();
}


// takes an lvalue and returns a Future<T&>
template<typename T>
auto take(T& t) -> Future<T&>
{
    T* pt = &t;
    return Future<T&>(move(std::async([=]()-> T& { return (*pt);})));
}


int main()
{    
    int n = 0;   
    take(n).then([](int& n) -> int& { return n += 1; }) // explicit return type required
           .then([](int& n) { n += 1; })
           .finally([&]() { std::cout << n << std::endl; });
}

#include <iostream>
#include <future>
#include <type_traits>


template<typename T>
struct Future : std::shared_future<T>
{
    Future(std::shared_future<T> f) :
        std::shared_future<T>(std::forward<std::shared_future<T>>(move(f)))
    {
    }
    
    template<typename F>
    auto then(F f) -> Future<decltype(f(std::declval<T>()))>
    {
        typedef decltype(f(std::declval<T>())) R;
        return Future<R>(std::move(std::async(std::launch::async, [=] {
                return f(this->get());
        })));
    }
};

    
template<typename T>
auto take(T t) -> Future<T>
{
    return Future<T>(std::move(std::async([=]{return t;})));
}





int main()
{
    auto inc = [](int n) { return n + 1; };
    
    take(0).then([](int n) { std::cout << n << std::endl; });
    
    take(0).then(inc)
           .then([](int n) { std::cout << n << std::endl; });
           
    take(0).then(inc)
           .then(inc)
           .then([](int n) { std::cout << n << std::endl; });
           
    auto n = take(0).then(inc)
                    .then(inc)
                    .then(inc)
                    .get();
                    
    std::cout << n << std::endl;
}



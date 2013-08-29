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
        return Future<R>(std::move(std::async(std::launch::async, [=]() { return f(this->get()); })));
    }
};


template<typename T>
auto take(T& t) -> Future<T>
{
    T* pt = &t;
    return Future<T>(std::move(std::async([=]{return (*pt);})));
}


int main()
{
    auto inc = [](int n) { return n + 1; };
    
    int n = 0;    
    take(n).then(inc).then([](int n) { std::cout << n << std::endl; });
        
        
    Future<std::string> fut(std::async([] { return std::string("abc"); }));
    fut.then([](const std::string& s) { return s+s; })       
       .then([](const std::string& s) { std::cout << s << std::endl; })       
       .wait();
    
}

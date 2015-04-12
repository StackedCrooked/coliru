#include <string>
#include <vector>
#include <thread>
#include <future>
#include <memory>
#include <iostream>

struct foo
{
    std::promise<void> p;
    
    foo(std::promise<void> p) : p(std::move(p)) {}
    
    foo(foo&&) = default;
    foo & operator=(foo&&) = default;
    
    void operator()() { std::cout << "X"; }
};

template<typename T>
struct shared_function
{
    std::shared_ptr<T> t;
    shared_function(T && t) : t(std::make_shared<T>(std::move(t))) {}
    
    template<typename... P>
    auto operator()(P... p) { return (*t)(std::forward<T>(p)...); }
};

template<typename T>
shared_function<T> make_shared_function(T && t)
{
    return shared_function<T>(std::move(t));
}

int main()
{
    std::promise<void> p;
    std::future<void> f = p.get_future();
    std::function<void()> fun(make_shared_function(foo(std::move(p))));
    fun();
}

#include <iostream>
#include <future>
#include <type_traits>


template<typename T>
struct call_
{
    call_(std::future<T>& f) : fut(f) {}
    
    template<typename F>
    auto then(F f) -> std::future<decltype(f())>
    {
        return std::async([=]{ return f(fut.get()); });
    }
    
    std::shared_future<T> fut;    
};


template<typename F, typename ...Args>
auto call(F f, Args&& ...args) -> call_<decltype(f(std::declval<Args>()...))>
{
    typedef decltype(f(std::declval<Args>()...)) R;
    return call_<R>(std::async(f, std::forward<Args>(args)...));
}



int main()
{    
    auto inc = [](int n) { return n + 1; };
    call(inc, 1).then(inc).then(inc);
}
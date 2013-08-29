#include <iostream>
#include <future>
#include <type_traits>


template<typename T>
struct call_helper;


// F takes no arguments 
template<typename F>
auto call(F&& f) -> call_helper<decltype(f())>
{
    return call_helper<decltype(f())>(
        std::async(std::forward<F>(f))
    );
}


template<typename F, typename Arg>
auto call(F&& f, Arg&& arg) -> call_helper<decltype(std::forward<F>(f)(std::forward<Arg>(arg)))>
{
    return call_helper<decltype(std::forward<F>(f)(arg))>(
        std::async(std::forward<F>(f), std::forward<Arg>(arg))
    );
}


template<typename T>
struct call_helper
{
    call_helper(std::shared_future<T>&& f) : fut(std::forward<std::shared_future<T>>(f)) {}
    
    template<typename F>
    auto then(F&& f) -> call_helper<decltype(f(std::declval<T>()))>
    {
        return call(std::forward<F>(f), fut.get());
    }
    
    T get() { return fut.get(); }
    
    void wait() { fut.wait(); }
    
    std::shared_future<T> fut;
};


template<>
struct call_helper<void>
{
    call_helper(std::shared_future<void> f) : fut(f) {}
    
    template<typename R>
    call_helper<R> then(std::function<R()> f)
    {
        return call_helper<R>(
            std::async([=] {
                fut.wait();
                return f();
            })
        );
    }
    
    void wait() { fut.wait(); }
    
    std::shared_future<void> fut;    
};

int main()
{    
    // increment function
    auto inc = [](int n) { return n + 1; };    
    
    // call increment(0)
    std::cout << call(inc, 0).get() << std::endl;
    
    // increment(increment(0))
    std::cout << call(inc, 0).then(inc).get() << std::endl;
    
    // increment(increment(increment(0)))
    std::cout << call(inc, 0).then(inc).then(inc).get() << std::endl;
    
    
    // internal compiler error
//    auto print = [](std::string message) { std::cout << message << std::endl; };
//    call(print, "hello").wait();
}
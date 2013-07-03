#include <iostream>
#include <future>
#include <type_traits>


template<typename T>
struct call_helper;


// F takes no arguments 
template<typename F>
auto call(F f) -> call_helper<decltype(f())>
{
    return call_helper<decltype(f())>(
        std::async(std::launch::async, f)
    );
}


template<typename F, typename Arg>
auto call(F f, Arg&& arg) -> call_helper<decltype(f(arg))>
{
    return call_helper<decltype(f(arg))>(
        std::async(std::launch::async, f, std::forward<Arg>(arg))
    );
}


template<typename T>
struct call_helper
{
    call_helper(std::shared_future<T>&& f) :
        future_(std::forward<std::shared_future<T>>(f))
    {
    }
    
    template<typename F>
    auto then(F f) -> call_helper<decltype(f(std::declval<T>()))>
    {
        return call_helper<decltype(f(std::declval<T>()))>(
            std::async(std::launch::async, [=]{ 
                return f(future_.get());
            })
        );
    }
    
    T get() { return future_.get(); }
    
    void wait() { future_.wait(); }
    
    std::shared_future<T> future_;
};


template<>
struct call_helper<void>
{
    call_helper(std::shared_future<void> f) : future_(move(f)) {}
    
    template<typename F>
    auto then(F f) -> call_helper<decltype(f())>
    {
        return call_helper<decltype(f())>(
            std::async(std::launch::async, [=] {
                future_.wait();
                return f();
            })
        );
    }
    
    template<typename F, typename Arg>
    auto then(F f, Arg&& arg) -> call_helper<decltype(f(arg))>
    {
        return call_helper<decltype(f(arg))>(
            std::async(std::launch::async, [=] {
                future_.wait();
                return f(arg);
            })
        );
    }
    
    void wait() { future_.wait(); }
    
    std::shared_future<void> future_;    
};


auto call() -> call_helper<void>
{
    return call_helper<void>(std::async([]{}));
}


//
// increment function (takes one argument)
//
auto inc = [](int n) {
    return n + 1;
};


//
// print function (takes no arguments)
//
void print(const std::string& s)
{
    std::cout << s;
}

int main()
{    
    std::cout << call(inc, 0).get()
              << call(inc, 0).then(inc).get()
              << call(inc, 0).then(inc).then(inc).get()
              << call(inc, 0).then(inc).then(inc).then(inc).get()
              << call(inc, 0).then(inc).then(inc).then(inc).then(inc).get()
              << std::endl;
                  
    
    call()
        .then(print, "A")
        .then(print, "B")
        .then(print, "C")
        .then(print, "D")
        .then(print, "E")
        .wait();
}



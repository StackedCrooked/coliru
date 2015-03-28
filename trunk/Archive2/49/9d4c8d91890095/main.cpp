#include <tbb/concurrent_queue.h>
#include <iostream>
#include <memory>


struct function_wrapper
{
    template<typename F>
    function_wrapper(F&& f) : 
        impl(new RealImpl<F>(std::forward<F>(f))) // "C++ concurrency in action" uses std::move(f) here..
                                                  // shouldn't it be forward because (incoming) F is a "deduced" type?
    {
    }
    
    function_wrapper() = default;
    
    function_wrapper(function_wrapper&&) = default;
    function_wrapper& operator=(function_wrapper&&) = default;
    
    void operator()()
    {
        impl->call();
    }
    
private:
    struct Impl
    {
        virtual ~Impl() {}          // private class => compiler "knows" that outsiders can not inherit => devirtualization possible?
        virtual void call() = 0;
    };
    
    template<typename F>
    struct RealImpl : Impl
    {        
        RealImpl(F&& f) : f(std::move(f)) {} // move seems the right choice here (F is not deduced)
        virtual void call() { f(); }
        F f;
    };
    
    std::unique_ptr<Impl> impl;
};


template<typename T>
struct thread_safe_queue
{
};


int main()
{   
    thread_safe_queue<function_wrapper> queue; // better than std::function
    
}


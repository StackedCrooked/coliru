#include <iostream>
#include <tuple>


template<typename>
struct Signature;

template<typename R, typename... Args>
struct Signature<R(Args...)>
{
    typedef R result_type;
    typedef std::tuple<Args...> argument_type;
};

template<typename Obj, typename R, typename ...Args>
Signature<R(Args...)> get_signature(R (Obj::*)(Args...) const)
{
    return Signature<R(Args...)>{};
}

template<typename Obj, typename R, typename ...Args>
Signature<R(Args...)> get_signature(R (Obj::*)(Args...))
{
    return Signature<R(Args...)>{};
}

template<typename R, typename ...Args>
Signature<R(Args...)> get_signature(R(*)(Args...))
{
    return Signature<R(Args...)>{};
}


template<typename>
struct Composer;


template<typename R, typename ...Args>
struct Composer<R(Args...)>
{
    template<template<class> class ...F>
    static auto compose(F<R(Args...)>&& ...f)
    {
        return [=](Args&& ...args) {
            int array[] = { (f(std::forward<Args>(args)...), 1)... };
            (void)array;
        };
    }
};


template<template<class> class F, typename Sig>
auto operator,(F<Sig>&& f, F<Sig>&& g)
{
    return Composer<decltype(get_signature(f))>::compose(f, g);
    
}


void foo() {}


int main()
{
    
    auto a = []() { std::cout << "a"; };    
    auto b = [](int n) { std::cout << n; };
    
    
    (a, a, a, a)();
    
    std::cout << std::endl;   
    
    (b, b, b)(1);
}

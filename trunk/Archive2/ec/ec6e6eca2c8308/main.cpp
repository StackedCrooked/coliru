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


void foo(){}


int main()
{
    auto a = []{};
    get_signature(&decltype(a)::operator());
    
    auto b = [](int n) { return n == 0; };
    get_signature(&decltype(b)::operator());
    
    get_signature(&foo);
}

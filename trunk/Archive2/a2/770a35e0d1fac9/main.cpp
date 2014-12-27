#include <iostream>
#include <utility>
#include <type_traits>


template <typename F>
struct return_type;
    
template <typename R, typename... Args>
struct return_type<R(Args...)> { using type = R; };

template <typename R, typename... Args>
struct return_type<R(*)(Args...)> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...)> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) &> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) &&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) volatile> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) volatile&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) volatile&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const volatile> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const volatile&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const volatile&&> { using type = R; };

template <typename Function, typename... Args>
auto call_function(Function&& f, Args&&... args)
    -> typename return_type<typename std::remove_reference<Function>::type>::type
{
    return std::forward<Function>(f)(std::forward<Args>(args)...);
}
    
template <typename Function, typename Class>
auto call_member_function(Function&& f, Class* instance)
    -> typename return_type<typename std::remove_reference<Function>::type>::type
{
    return (instance->*std::forward<Function>(f))();
}

struct F
{
    int f() { std::cout << "F::f()" << std::endl; return 0; }
};

int f() { std::cout << "f()" << std::endl; return 0; }

int main()
{
    F instance;
    static_assert(std::is_same<decltype(call_function(f)), int>{}, "!");
    static_assert(std::is_same<decltype(call_member_function(&F::f, &instance)), int>{}, "!"); 
}

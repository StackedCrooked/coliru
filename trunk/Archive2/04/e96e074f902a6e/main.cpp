#include <iostream>
#include <utility>
#include <type_traits>

template <typename F>
struct return_type;

template <typename R, typename... Args>
struct return_type<R(Args...)> { using type = R; };

template <typename R, typename... Args>
struct return_type<R(*)(Args...)> { using type = R; };

template <typename Function, typename... Args>
auto call_function(Function&& f, Args&&... args)
    -> typename return_type<typename std::remove_reference<Function>::type>::type
{
    return std::forward<Function>(f)(std::forward<Args>(args)...);
}

int f() { std::cout << "f()" << std::endl; return 0; }

int main()
{
    static_assert(std::is_same<decltype(call_function(f)), int>{}, "!");
}

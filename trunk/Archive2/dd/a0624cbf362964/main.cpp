#include <functional>
#include <tuple>
#include <utility>
#include <cstddef>

template <typename R, typename... Args, std::size_t... Is>
std::function<R(typename std::tuple_element<Is, std::tuple<Args...>>::type...)> pop_last(std::index_sequence<Is...>);

template <typename R, typename... Args>
auto pop_last() -> decltype(pop_last<R, Args...>(std::make_index_sequence<sizeof...(Args) - 1>{}));

template <typename T>
struct combinator_traits : combinator_traits<decltype(&T::template operator()<T>)> {};

template <typename C, typename R, typename... Args>
struct combinator_traits<R(C::*)(Args...)>
{
    using result_type = decltype(pop_last<R, Args...>());
};

template <typename C, typename R, typename... Args>
struct combinator_traits<R(C::*)(Args...)const>
    : combinator_traits<R(C::*)(Args...)> {};

struct dummy {};

// Tests:
#include <type_traits>
#include <iostream>

int foo(int x)
{
    if (x < 2)
        return 1;
    return foo(x - 1) + foo(x - 2);
}

int main()
{
    auto fib = [](int x, auto myself = dummy{}) -> int
    {
        if (x < 2)
            return 1;
        return myself(x - 1) + myself(x - 2);
    };
    
    static_assert(std::is_same<combinator_traits<decltype(fib)>::result_type, std::function<int(int)>>::value, "!");
    std::cout << fib(5, foo) << std::endl; // 8
}

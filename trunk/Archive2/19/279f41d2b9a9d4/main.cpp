#include <utility>
#include <cstddef>
#include <tuple>
#include <functional>

template <typename T>
struct lambda_traits : lambda_traits<decltype(&T::template operator()<T>)> {};

template <typename C, typename R, typename... Args>
struct lambda_traits<R(C::*)(Args...)const>
{
    using return_type = R;
    
    static constexpr std::size_t arity = sizeof...(Args);
    
    template <std::size_t index>
    struct arg
    {
        using type = typename std::tuple_element<index, std::tuple<Args...>>::type;
    };
};
template <typename C, typename R, typename... Args>
constexpr std::size_t lambda_traits<R(C::*)(Args...)const>::arity;

template <typename F, typename = lambda_traits<F>, typename = std::make_index_sequence<lambda_traits<F>::arity - 1>>
struct combinator_traits;

template <typename F, typename T, std::size_t... Is>
struct combinator_traits<F, T, std::index_sequence<Is...>>
{
    using return_type = std::function<typename T::return_type(typename T::template arg<Is + 1>::type...)>;
};

// Tests:
#include <iostream>

template <typename T>
typename combinator_traits<T>::return_type Y(T t)
{
    return {};
}

template <typename T> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

int main()
{    
    auto fib = [](auto myself, int x)
    {
        if(x < 2)
            return 1;
        return myself(myself, x - 1) + myself(myself, x - 2);
    };
    
    TD<decltype(Y(fib))>();
    
    std::function<int(int)> f = Y(fib);
}

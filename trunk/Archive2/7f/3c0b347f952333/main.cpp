#include <functional>
#include <cstddef>
#include <utility>
#include <tuple>

template <std::size_t N, typename Type, typename... Types>
struct n_ary_function
{
    using type = typename n_ary_function<N - 1, Type, Type, Types...>::type;
};

template <typename Type, typename... Types>
struct n_ary_function<0, Type, Types...>
{
    using type = std::function<void(Types...)>;
};

using placeholders_list = std::tuple<decltype(std::placeholders::_1)
                                   , decltype(std::placeholders::_2)
                                   , decltype(std::placeholders::_3)
                                   , decltype(std::placeholders::_4)
                                   , decltype(std::placeholders::_5)
                                   , decltype(std::placeholders::_6)
                                   , decltype(std::placeholders::_7)
                                   , decltype(std::placeholders::_8)
                                   , decltype(std::placeholders::_9)
                                   , decltype(std::placeholders::_10)
                                   >;

template <typename F>
struct arity;

template <typename R, typename... Args>
struct arity<std::function<R(Args...)>>
{
    static constexpr std::size_t value = sizeof...(Args);
};

template <typename F, typename T, std::size_t... Ints>
auto binder(F f, T t, std::index_sequence<Ints...>)
{
    return std::bind(f, t, typename std::tuple_element<Ints, placeholders_list>::type{}...);
}

template <typename F, typename T>
auto myBind(F f, T t)
{
    return binder(f, t, std::make_index_sequence<arity<F>::value - 1>{});
}

#include <iostream>

void foo(int a, int b, int c, int d, int e)
{
    std::cout << a << b << c << d << e << std::endl;
}

int main()
{
    n_ary_function<5, int>::type f = foo;    
    n_ary_function<4, int>::type b = myBind(f, 1);
    b(2, 3, 4, 5);
}

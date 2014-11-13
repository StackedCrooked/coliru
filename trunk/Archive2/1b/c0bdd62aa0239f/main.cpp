#include<type_traits>
#include<tuple>
#include<iostream>

template<typename... Ts, typename FunctionType>
void for_each(std::tuple<Ts...> &, FunctionType, std::integral_constant<size_t, sizeof...(Ts)>) {}

template<std::size_t I, typename... Ts, typename FunctionType, typename = typename std::enable_if<I!=sizeof ...(Ts)>::type >
void for_each(std::tuple<Ts...>& t, FunctionType f, std::integral_constant<size_t, I>)
{
	f(std::get<I>(t));
	for_each(t, f, std::integral_constant<size_t, I + 1>());
}

template<typename... Ts, typename FunctionType>
void for_each(std::tuple<Ts...>& t, FunctionType f)
{
	for_each(t, f, std::integral_constant<size_t, 0>());
}


int main()
{
    auto some = std::make_tuple("I am good", 255, 2.1);
    for_each(some, [](auto const&x) { std::cout << x << std::endl; });
}
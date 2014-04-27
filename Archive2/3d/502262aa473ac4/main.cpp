#include <type_traits>
#include <iostream>
#include <tuple>

template<typename T>
struct is_tuple : public std::false_type {};

template<typename... Ts>
struct is_tuple<std::tuple<Ts...>> : public std::true_type {};

template<typename T>
typename std::enable_if<!is_tuple<T>::value, std::tuple<T>>::type tupleize(T && t)
{
    return std::tuple<T>{ std::forward<T>(t) };
}

template<typename T>
typename std::enable_if<is_tuple<T>::value, T>::type tupleize(T && t)
{
    return std::forward<T>(t);
}

template<typename F, typename T>
decltype(auto) unpack(F && f, T && t)
{
    return f(std::get<3>(t));
}

template<typename F, typename... Ts>
decltype(auto) wanted(F && f, Ts &&... ts)
{
    return unpack(std::forward<F>(f), std::tuple_cat(tupleize(std::forward<Ts>(ts))...));
}

int main()
{
    wanted([](int i) { std::cout << i << std::endl; }, 1, 2, std::make_tuple(3, 4, 5));
}

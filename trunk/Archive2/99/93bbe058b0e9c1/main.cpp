#include <tuple>
#include <type_traits>
#include <utility>
#include <stdexcept>
#include <boost/variant.hpp>

template<template<class...> class T, class... As>
using invoke_t = typename T<As...>::type;

template<class T>
using unqual_t = invoke_t<std::remove_cv, invoke_t<std::remove_reference, T>>;

template<int...> struct seq{ using type = seq; };
template<int I, int... Is> struct gen_seq : gen_seq<I - 1, I - 1, Is...>::type{};
template<int... Is> struct gen_seq<0, Is...> : seq<Is...>{};

template<class T>
using gen_seq_for = typename gen_seq<std::tuple_size<unqual_t<T>>::value>::type;

template<int I>
using int_ = std::integral_constant<int, I>;

template<int I, class T>
struct tagged{ T value; };

template<int I, class T>
tagged<I, T> make_tagged(T&& v){ return { std::forward<T>(v) }; }

template<class Seq, class T> struct get_variant;
template<int... Is, class... Ts>
struct get_variant<seq<Is...>, std::tuple<Ts...>&>{ using type = boost::variant<tagged<Is, Ts&>...>; };
template<int... Is, class... Ts>
struct get_variant<seq<Is...>, std::tuple<Ts...> const&>{ using type = boost::variant<tagged<Is, Ts const&>...>; };
template<int... Is, class... Ts>
struct get_variant<seq<Is...>, std::tuple<Ts...>&&>{ using type = boost::variant<tagged<Is, Ts&&>...>; };

template<class T>
using get_variant_t = invoke_t<get_variant, gen_seq_for<T>, T>;

template<class T>
get_variant_t<T> get(std::size_t i, T&& t, int_<0>)
{
    if (i == 0)
        return make_tagged<0>(std::get<0>(std::forward<T>(t)));
    throw std::out_of_range("runtime get: index out of range");
}

template<class T, int I>
get_variant_t<T> get(std::size_t i, T&& t, int_<I>)
{
    if (i == I)
        return make_tagged<I>(std::get<I>(std::forward<T>(t)));
    return get(i, std::forward<T>(t), int_<I - 1>{});
}

template<class Tuple>
get_variant_t<Tuple> get(std::size_t i, Tuple&& t)
{
    static constexpr std::size_t size = std::tuple_size<unqual_t<Tuple>>::value;
    static_assert(size > 0, "runtime get: empty tuple not allowed");
    return get(i, std::forward<Tuple>(t), int_<size - 1>{});
}

#include <iostream>

int main()
{
    std::tuple<float, bool, double, double> t(42.3, true, 3.14, 1337.4);
    int i = 0;
    auto var = get(i, t);
    if (var.which() == i)
        std::cout << "yay";
    else
        std::cout << "nay";
}
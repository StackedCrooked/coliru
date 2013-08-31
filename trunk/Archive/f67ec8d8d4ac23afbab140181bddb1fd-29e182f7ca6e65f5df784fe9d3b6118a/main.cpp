#include <type_traits>

template<unsigned...> struct seq{ using type = seq; };
template<unsigned I, unsigned... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<unsigned, class T> struct holder{ using type = T; };

template<class T, class S = void>
struct type_switch;
template<template<class...> class TT, class... Ts>
struct type_switch<TT<Ts...>, void> : type_switch<TT<Ts...>, typename gen_seq<sizeof...(Ts)>::type>{};
template<template<class...> class TT, class... Ts, unsigned... Is>
struct type_switch<TT<Ts...>, seq<Is...>> : holder<Is, Ts>...{};

template<unsigned I, class T>
holder<I, T> select(holder<I, T>);

template<unsigned I, class T>
using TemplateArgument = typename decltype(select<I>(type_switch<T>{}))::type;

// ***

template<class... Ts> struct test{};

int main(){
    static_assert(std::is_same<int, TemplateArgument<4, test<bool, double, float, char, int, long>>>(), "...");
}
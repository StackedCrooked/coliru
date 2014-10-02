#include <cstddef>
#include <type_traits>

template<typename T>
struct identity {
    using type = T;
};

template<size_t N>
using Const = std::integral_constant<size_t, N>;

// better type list

template<typename... Args>
struct list : identity<list<Args...>> {};

template<typename List>
struct empty;

template<template<typename...> class S, typename... Args>
struct empty<S<Args...>> : std::integral_constant<bool, sizeof...(Args) == 0> {};

template<typename List>
struct back {};

template<typename T, typename... Args>
struct back<list<T, Args...>> : identity<typename back<list<Args...>>::type> {};

template<typename T>
struct back<list<T>> : identity<T> {};

int main() {
    using x = list<int, float, double, long double>;
    static_assert(empty<x>::value == false, "...");
    static_assert(std::is_same<back<x>::type, long double>::value, "...");
}

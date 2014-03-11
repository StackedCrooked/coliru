#include <tuple>

template<template<class...> class Container, int N, int I, class T, class... Args>
struct join_n;

template<template<class...> class Container, int N, int I, class... Joined, class Arg, class... Rest>
struct join_n<Container, N, I, std::tuple<Joined...>, Arg, Rest...>
: join_n<Container, N, I+1, std::tuple<Joined..., Arg>, Rest...>
{};

template<template<class...> class Container, int N, class... Joined, class Arg, class... Rest>
struct join_n<Container, N, N, std::tuple<Joined...>, Arg, Rest...>
{
    using type = Container<Joined...>;
    using rest = std::tuple<Arg, Rest...>;
};

template<template<class...> class Container, int N, class... Joined>
struct join_n<Container, N, N, std::tuple<Joined...>>
{
    using type = Container<Joined...>;
    using rest = std::tuple<>;
};

template<template<class...> class Container, int N, class Args, class Collected = std::tuple<>>
struct foo;

template<template<class...> class Container, int N, class... Args, class... Collected>
struct foo<Container, N, std::tuple<Args...>, std::tuple<Collected...>>
: foo<Container, N, typename join_n<Container, N, 0, std::tuple<>, Args...>::rest, std::tuple<Collected..., typename join_n<Container, N, 0, std::tuple<>, Args...>::type>>
{};

template<template<class...> class Container, int N, class... Collected>
struct foo<Container, N, std::tuple<>, std::tuple<Collected...>>
{
    using type = std::tuple<Collected...>;
};

template<class, class>
struct test {};

#include <iostream>
template<class T>
void print_type(T) { std::cout << __PRETTY_FUNCTION__ << "\n"; }

int main()
{
    print_type( foo<test, 2, std::tuple<int, double, int, char, int, bool>>::type{} );
}
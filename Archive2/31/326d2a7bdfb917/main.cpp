#include <array>
#include <vector>

// Separation of concerns: this handles rebinding of many-kinded containers
// It's non-intrusive (i.e. no need to change the containers) and extensible (can add kinds)

template<typename Container, typename Value>
struct rebind_container;

template<typename Container, typename Value>
using rebind_container_t = typename rebind_container<Container, Value>::type;

template<template<typename...> class Container, typename Old, typename Value>
struct rebind_container<Container<Old>, Value> {
    using type = Container<Value>;
};

template<
    template<typename, std::size_t, typename...> class Container,
    typename Old, std::size_t S, typename... Rest,
    typename Value
>
struct rebind_container<Container<Old, S, Rest...>, Value> {
    using type = Container<Value, S, Rest...>;
};

// Extensibility is achieved via adding more partial specializations as needed

// This consumes containers, using them at different element types without caring for their kinds

template<typename Container>
struct foo {
    using a = rebind_container_t<Container, int>;
    using b = rebind_container_t<Container, double>;
};

int main()
{
    // all valid instantiations
    foo<std::vector<int>>::a x {};
    foo<std::array<int, 14>>::b y {};
}
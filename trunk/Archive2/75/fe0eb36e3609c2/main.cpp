#include <type_traits>
#include <vector>
#include <map>

template<class, class = void> struct IsAssociativeContainer : std::false_type {};
template<class T> struct IsAssociativeContainer<T, typename std::enable_if<sizeof(typename T::key_type)!=0>::type> : std::true_type {};

template<class T, bool = IsAssociativeContainer<T>::value> struct Printer;

// I want this to match std::vector (and similar linear containers) 
template<template<class, class...> class T, class TV, class... TS> 
    struct Printer<T<TV, TS...>, false> { static void something(); };

// I want this to match std::map (and similar map-like containers)
template<template<class, class, class...> class TM, class TK, class TV, typename... TS> 
    struct Printer<TM<TK, TV, TS...>, true> { static void something(); };

int main() 
{
    // Both of these match the second specialization, which is only intended
    // for std::map (and similar map-like containers)
    Printer<std::vector<int>>::something();
    Printer<std::map<int, float>>::something();
}

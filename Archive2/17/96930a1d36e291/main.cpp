template<template<typename...> class T, typename>
struct instantiate_with_type_list { };

template<template<typename...> class T,
         template<typename...> class U,
         typename... Ts>
struct instantiate_with_type_list<T, U<Ts...>>
{
    using type = T<Ts...>;
};

#include <string>
#include <type_traits>
#include <iostream>

template<typename... Ts>
struct my_template { };

int main()
{
    using type_list = std::tuple<int, char, std::string>;
    using my_instantiation = instantiate_with_type_list<my_template, type_list>::type;

    std::cout << std::is_same<my_instantiation, my_template<int, char, std::string>>{};
}

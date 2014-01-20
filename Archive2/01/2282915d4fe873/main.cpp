#include <cstddef>
#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename... Args>
using template_alias = std::integral_constant<size_t, sizeof...(Args)>;
//struct template_alias : std::integral_constant<size_t, sizeof...(Args)> {}; // this works as expected

template <typename... Args>
void fun()
{
    typedef template_alias<Args...> alias_type;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "sizeof...(Args)                 = " << sizeof...(Args) << std::endl;
    std::cout << "template_alias<>::size()        = " << template_alias<>::value << std::endl;
    std::cout << "template_alias<Args...>::size() = " << template_alias<Args...>::value << std::endl;
    std::cout << "alias_type::size()              = " << alias_type::value << std::endl;
    std::cout << "---\n";
    std::cout << std::boolalpha << std::is_same<template_alias<>, template_alias<Args...>>::value << std::endl;
    std::cout << std::boolalpha << std::is_same<template_alias<>, alias_type>::value << std::endl;
    std::cout << "---\n";
    std::cout << std::boolalpha << (typeid(template_alias<>) == typeid(template_alias<Args...>)) << std::endl;
    std::cout << std::boolalpha << (typeid(template_alias<>) == typeid(alias_type)) << std::endl;
}

int main()
{
    fun<>();
}

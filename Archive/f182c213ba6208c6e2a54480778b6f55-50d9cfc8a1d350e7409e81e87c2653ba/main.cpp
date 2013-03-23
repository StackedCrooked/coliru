#include <iostream>
#include <utility>
#include <string>

template<template<typename ...> class Base, typename ...Args>
struct Derived : Base<Args...> {
    using base_type = Base<Args...>;
    using base_type::Base;
};


typedef Derived<std::basic_string, char, std::char_traits<char>, std::allocator<char>> String;

int main()
{    
    String s1("s1");
    std::string abc;
    String str(abc);
}
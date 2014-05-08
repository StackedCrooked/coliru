#include <vector>
#include <iostream>

template<template<typename... T> class C, typename T> struct is_template_of {
    static const bool value = false;
};
template<template<typename... T> class C, typename... X> struct is_template_of<C, C<X...>> {
    static const bool value = true;
};
int main() {
    std::cout << std::boolalpha << is_template_of<std::vector, std::vector<int>>::value;
}
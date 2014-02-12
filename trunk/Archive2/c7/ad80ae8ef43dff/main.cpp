#include <iostream>
#include <iterator>
#include <string>
#include <vector>

template<template<typename...> class T, typename E, typename... X>
void flatten_to_stream(T<E, X...> const& container, std::ostream& stream)
{
    std::copy(container.cbegin(), container.cend(), std::ostream_iterator<E>(stream));
}

int main()
{
    std::vector<std::string> v = {
        "hi", "guise", "i", "suck"
    };
    
    flatten_to_stream(v, std::cout);
}

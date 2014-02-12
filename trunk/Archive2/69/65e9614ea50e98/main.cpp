#include <iostream>
#include <iterator>
#include <string>
#include <vector>

template<typename T>
void flatten_to_stream(T const& container, std::ostream& stream)
{
    std::copy(container.cbegin(), container.cend(), std::ostream_iterator<typename T::value_type>(stream));
}

/**
 * Can something like this work?
 * I'm not sure how to write it (or if it is of any interest really).
 * 
 * template<template<typename E> class T>
 * void flatten_to_stream(T<E, ...> const& container, std::ostream& stream)
 * {
 *     std::copy(container.cbegin(), container.cend(), std::ostream_iterator<E>(stream));
 * }
 * 
 */

int main()
{
    std::vector<std::string> v = {
        "hi", "guise", "i", "suck"
    };
    
    flatten_to_stream(v, std::cout);
}

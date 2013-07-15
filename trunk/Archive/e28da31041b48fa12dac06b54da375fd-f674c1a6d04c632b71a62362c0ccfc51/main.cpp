#include <unordered_map>
#include <map>
#include <boost/unordered_map.hpp>
#include <iostream>

template<template <typename ... T> class MAP_CONTAINER>
void check_ends() {
    MAP_CONTAINER<int, int> m1, m2;
    std::cout << typeid(m1).name() << " - Different instances have " 
        << (m1.end() == m2.end() ? "the same" : "different") 
        << " ends" << std::endl;
}

int main() {
    check_ends<std::map> ();
    check_ends<std::unordered_map> ();
    check_ends<boost::unordered_map> ();

    return 0;
}
#include <unordered_map>
#include <map>
#include <boost/unordered_map.hpp>
#include <iostream>

template<class Key, class Value>
class std_map : public std::map<Key, Value> {};

template<class Key, class Value>
class std_unordered_map : public std::unordered_map<Key, Value> {};

template<class Key, class Value>
class boost_unordered_map : public boost::unordered_map<Key, Value> {};

template<template<class Key, class Value> class MAP_CONTAINER>
void check_ends() {
    MAP_CONTAINER<int, int> m1, m2;
    std::cout << typeid(m1).name() << " - Different instances have " 
        << (m1.end() == m2.end() ? "the same" : "different") 
        << " ends" << std::endl;
}

int main() {
    check_ends<std_map> ();
    check_ends<std_unordered_map> ();
    check_ends<boost_unordered_map> ();

    return 0;
}
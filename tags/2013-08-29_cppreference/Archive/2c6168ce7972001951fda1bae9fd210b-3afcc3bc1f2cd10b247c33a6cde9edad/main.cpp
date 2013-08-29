#include <iostream>
#include <string>

template<template<typename...> class Cont, typename... ContArgs>
inline void all(const Cont<ContArgs...> &str) {
    for(auto&& i : str) {
       std::cout << i;
    }
}


int main() {
    all(std::string("i3aa34"));
}
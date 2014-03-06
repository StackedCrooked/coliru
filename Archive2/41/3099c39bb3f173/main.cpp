#include <iostream>

template<template<typename> class> void f() { std::cout << "second.\n"; }

template<typename> class X {};
struct Y : X<int> { }; 

int main() {
    f<Y::X>();
}
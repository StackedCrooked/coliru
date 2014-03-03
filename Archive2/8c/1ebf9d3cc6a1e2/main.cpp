template<typename> void f();
template<template<typename> class> void f() {}

template<typename> class X {};
struct Y : X<int> { }; 

int main() {
    f<Y::template X>();
}
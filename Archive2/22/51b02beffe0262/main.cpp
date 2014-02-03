#include <iostream>

template<template<typename...> class C, typename... T>
struct is_valid_specialization {
    typedef struct { char _; } yes;
    typedef struct { yes _[2]; } no;

    template<template<typename...> class D>
    static yes test(D<T...>*);
    template<template<typename...> class D>
    static no test(...);

    constexpr static bool value = (sizeof(test<C>(0)) == sizeof(yes));
};

template<typename T>
struct Test1 { };

template<typename T1, typename T2>
struct Test2 { };

template<typename...>
struct TestV { };

int main() {
    std::cout << "Test1<T>: " << is_valid_specialization<Test1, int>::value << std::endl;
    std::cout << "Test2<T>: " << is_valid_specialization<Test2, int>::value << std::endl;
    std::cout << "TestV<T>: " << is_valid_specialization<TestV, int>::value << std::endl;
}

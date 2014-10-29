#include <tuple>

template<template<class...> class Template, class T>
struct Bind1 {
    template<class ...U>
    using type = Template<T, U...>;
};


int main(int argc, char** argv) {
    Bind1<std::tuple, int>::type<const char*, double> x { 2, "test", 5.6 };
    
    return 0;
}
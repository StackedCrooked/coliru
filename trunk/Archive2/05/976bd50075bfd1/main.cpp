#include <iostream>
#include <string>
#include <vector>

namespace std {
    
template <typename T, typename U>
T as(U&& u)
{
    T ret = std::forward<U>(u);
    return ret;
}

template <typename T, typename U>
T to(U&& u)
{
    T ret(std::forward<U>(u));
    return ret;
}

}

struct A1{};
struct A2{
    A2(const A1&){}
};
struct B1{};
struct B2
{
    explicit B2(const B1&){}
};

struct C2{};
struct C1
{
    operator C2() const{ return C2(); }
};

struct D2{};
struct D1
{
    explicit operator D2() const{ return D2(); }
};

int main()
{
    int i = 0;
    std::as<int&>(i);       // OK
    std::to<int&>(i);       // OK
    std::as<const int&>(i); // OK
    std::to<const int&>(i); // OK
    const int ci = 0;
//  std::as<int&>(ci);       // Error: invalid initialization of reference of type 'int&' from expression of type 'const int'
//  std::to<int&>(ci);       // Error: invalid initialization of reference of type 'int&' from expression of type 'const int'
    std::as<const int&>(ci); // OK
    std::to<const int&>(ci); // OK
    
    A1 a;
    B1 b;
    C1 c;
    D1 d;
    std::as<A2>(a); // OK
    std::to<A2>(a); // OK
//  std::as<B2>(b); // Error: conversion from 'B1' to non-scalar type 'B2' requested
    std::to<B2>(b); // OK
    std::as<C2>(c); // OK
    std::to<C2>(c); // OK
//  std::as<D2>(d); // Error: conversion from 'D1' to non-scalar type 'D2' requested
    std::to<D2>(d); // OK
}

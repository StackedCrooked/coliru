template<typename A, typename B, typename C>
struct SomeType {};

struct T1 {};
struct T2 {};
struct T3 {};

using MyType = SomeType<T1, T2, T3>; // This is the type to pass to the functor

template<template<typename...> class, typename...> struct SomeOperation {};

template <typename T>
struct MetaFunction;

template <template<typename...> class MyType, typename ... Args>
struct MetaFunction<MyType<Args...>>
{
  using type = SomeOperation<MyType, Args...>;
};

int main()
{
    // I want to be able to call my functor like this:
    MetaFunction<MyType>::type;
}
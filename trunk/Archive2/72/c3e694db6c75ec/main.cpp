#include <type_traits>

template<typename FUN, typename... ARGS>
struct eval_impl;

template<template<typename...> class F, typename... PLACEHOLDERS, typename... ARGS>
struct eval_impl<F<PLACEHOLDERS...>, ARGS...> : public F<ARGS...> {};

template<typename EXPRESSION, typename... ARGS>
using eval = typename eval_impl<EXPRESSION, ARGS...>::type;

struct _1 {};
struct _2 {};
struct _3 {};
struct _4 {};

template<typename ARG, typename... ARGS>
struct first_of { using type = ARG; };

using call = eval<first_of<_1,_2,_3,_4>, bool, float, char, int>;

int main ()
{
    static_assert(std::is_same<call, bool>{}, "Oops!");
}

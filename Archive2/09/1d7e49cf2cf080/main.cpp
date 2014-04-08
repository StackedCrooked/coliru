#include <type_traits>

template<typename FUN, typename... ARGS>
struct eval_impl;

template<template<typename...> class F, typename... PLACEHOLDERS, typename... ARGS>
struct eval_impl<F<PLACEHOLDERS...>, ARGS...> : public F<ARGS...> {};

template<typename EXPRESSION, typename... ARGS>
using eval = typename eval_impl<EXPRESSION, ARGS...>::type;

template<template<typename...> class F, typename... ARGS>
using alias_eval = F<ARGS...>;

struct _1 {};
struct _2 {};
struct _3 {};
struct _4 {};

template<typename ARG, typename... ARGS>
struct first_of { using type = ARG; };

template<typename ARG , typename... ARGS>
using first_of_t = typename first_of<ARG, ARGS...>::type;

using call = eval<first_of<_1,_2,_3,_4>, bool, float, char, int>;

using alias_call = alias_eval<first_of_t, bool, float, char, int>;

int main ()
{
    static_assert(std::is_same<call, bool>{}, "Oops!");
	static_assert(std::is_same<alias_call, bool>{}, "Oops!");
}

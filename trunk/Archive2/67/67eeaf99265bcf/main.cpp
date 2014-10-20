#include <tuple>
 
namespace detail
{
 
template<class...>
struct type_list {};

template<class T, class X>
struct prepend_t;

template<class T, class... X>
struct prepend_t<T, type_list<X...>>
{
    using type = type_list<T, X...>;
};

template<class T, class X>
using prepend = typename prepend_t<T, X>::type;
 
template <typename T>
struct Unfold
{
	using type = type_list<T>;
};

template<template<class...> class Branch, typename T>
struct Unfold<Branch<T>>
{
	using type = prepend<Branch<T>, typename Unfold<T>::type>;
};
 
}
 
template <typename Expression>
struct Unfold : detail::Unfold<Expression> {};
 
template <typename... Children>
struct Branch
{};
 
struct Leaf
{};
 
// Add wrap Leaf in Branch N number of times:
template <int N, typename T = Leaf>
struct Nest
{
using type = typename Nest<N-1, Branch<T>>::type;
};
 
template <typename T>
struct Nest<0, T>
{
using type = T;
};
 
// here is the input expression:
using Expression = typename Nest<DEPTH>::type;
 
int main()
{
Expression e;
typename Unfold<Expression>::type x; // disable this line for "generate expression only"
return 0;
} 
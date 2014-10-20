#include <tuple>
 
namespace detail
{
 
template<class...>
struct type_list {};

template<class T, class X>
struct append_t;

template<class T, class... X>
struct append_t<T, type_list<X...>>
{
    using type = type_list<X..., T>;
};

template<class T, class X>
using append = typename append_t<T, X>::type;

template<class T, class U>
struct join_t;

template<class... T, class... U>
struct join_t<type_list<T...>, type_list<U...>>
{
	using type = type_list<T..., U...>;
};

template<class T, class U>
using join = typename join_t<T, U>::type;
 
template <typename T>
struct Unfold
{
	using type = type_list<T>;
};

template<template<class...> class Branch>
struct Unfold<Branch<>>
{
	using type = type_list<>;
};

template<template<class...> class Branch, class T, class... U>
struct Unfold<Branch<T, U...>>
{
	using unfold_T = typename Unfold<T>::type;
	using x = append<T, unfold_T>;
	using y = join<x, typename Unfold<Branch<U...>>::type>;
	using type = y;
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

#include <iostream>

template<class T>
void print_type()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

int main()
{
Expression e;
typename Unfold<Expression>::type x; // disable this line for "generate expression only"
print_type<decltype(x)>();
return 0;
} 
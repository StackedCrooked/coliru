#include <type_traits>

template<typename...> struct void_ { using type = void; };
template<typename... Ignored> using void_t = typename void_<Ignored...>::type;

template<typename Expr> struct expr;
template<typename... Reqs> struct all_of {};

template<typename A, typename B = A>
struct EqualityComparable {
    template<typename X = A, typename Y = B>
    auto requires(X const& x, Y const& y) -> all_of<
        expr<decltype( x == y )>,
        expr<decltype( x != y )>
    >;
};

template<typename Sig>
struct ret {};

template<typename R, typename Class, typename... Args>
struct ret<R (Class::*)(Args...)> { using type = R; };

template<typename Concept, typename Sfinae = void>
struct requirements {};

template<template<typename...> class Concept, typename... Args>
struct requirements<Concept<Args...>, void_t<decltype( &Concept<Args...>::template requires<Args...> )>>
: ret<decltype( &Concept<Args...>::template requires<Args...> )> {};

struct pathological {};
// non-const!
int operator==(pathological&, pathological&);
int operator!=(pathological&, pathological&);

int main()
{
    // yes
    all_of<expr<bool>, expr<bool>> {} = requirements<EqualityComparable<int>>::type {};
    
    // yes
    all_of<expr<int>, expr<int>> {} = requirements<EqualityComparable<pathological&>>::type {};
    
    // no
    requirements<EqualityComparable<pathological>>::type {};
}
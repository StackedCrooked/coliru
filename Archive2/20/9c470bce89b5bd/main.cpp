#include <type_traits>

template<typename...> struct void_ { using type = void; };
template<typename... Ignored> using void_t = typename void_<Ignored...>::type;

template<typename Expr> struct expr;
template<typename... Reqs> struct all_of {};

template<typename A, typename B = A>
struct EqualityComparable {
    template<typename X = A, typename Y = B>
    static auto requires(X const& x, Y const& y) -> all_of<
        expr<decltype( x == y )>,
        expr<decltype( x != y )>
    >;
};

template<typename Sig>
struct ret {};

template<typename R, typename... Args>
struct ret<R (*)(Args...)> { using type = R; };

template<typename Concept> struct scope;

template<template<typename...> class Concept, typename... Args>
struct scope<Concept<Args...>>: private Concept<Args...> {
    using base_type = Concept<Args...>;
    using base_type::requires;
    
    template<typename... A> decltype( &scope::template requires<A...> ) tell_me_dammit();
    template<typename... Dependee>
    static scope& declval();
    
    template<typename D = void, typename Sfinae = void>
    struct wat {};
    
    template<typename D>
    struct wat<D, void_t<decltype( declval<D>().tell_me_dammit<Args...>() )>>
    : ret<decltype( declval().tell_me_dammit<Args...>() )> {};
    
    using type = wat<>;
};

template<typename Concept>
struct requirements: scope<Concept>::template wat<void> {};

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
    requirements<EqualityComparable<pathological>> {};
}
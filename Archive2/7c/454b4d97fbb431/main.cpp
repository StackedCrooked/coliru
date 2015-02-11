#include <type_traits>

// The goal here is to create some generally useful tools, then solve `pow` in as few lines.  The generally useful type tools aren't all that bulky either.

// So, first a library for type list manipulation.
    
    template<class...>struct types{using type=types;};

// Concat two type lists:
    
    template<class types1,class types2>struct concat;
    template<class...types1,class...types2>struct concat<
      types<types1...>,
      types<types2...>
    >:types<types1...,types2...>{};
    template<class A,class B>using concat_t=typename concat<A,B>::type;
// Apply type function Z to each element of a list:
    
    template<template<class...>class Z, class types> struct apply;
    template<template<class...>class Z, class...Ts>
    struct apply<Z,types<Ts...>>:
      types< Z<Ts>... >
    {};
    template<template<class...>class Z, class types>
    using apply_t=typename apply<Z,types>::type;
// partial template application:

    template<template<class...>class Z, class T>
    struct partial {
      template<class... Ts>
      struct apply:Z<T,Ts...> {};
      template<class... Ts>
      using apply_t=typename apply<Ts...>::type;
    };
// take lhs, and apply Z<lhs, *> on rhs:

    template<template<class, class...>class Z, class lhs, class types>
    using expand_t=apply_t<partial<Z,lhs>::template apply_t, types>;
// solve the problem:

    template<class T>struct pow; // fail if not given a package
    template<>struct pow<types<>>:types<types<>>{};
    template<class T>using pow_t=typename pow<T>::type;
    template<class T0,class...Ts>struct pow<types<T0,Ts...>>:
      concat_t<
        expand_t< concat_t, types<T0>, pow_t<types<Ts...>> >,
        pow_t<types<Ts...>>
      >
    {};
    

using foo = types<int>;
using bar = types<int, char>;

int main()
{
    using p = pow_t<foo>;
    static_assert(std::is_same<p, types<types<int>,types<>>>::value, "foo!");
    static_assert(std::is_same<pow_t<bar>, types<types<int, char>,types<int>, types<char>, types<>>>::value, "bar!");
}
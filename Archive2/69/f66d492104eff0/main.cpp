#include <type_traits>
#include <vector>

namespace shiny {
//   Boilerplate types pack:

    template<class...>struct types {using type=types;};
// In C++1z, reimplemented here:

    template<class...>struct voider{using type=void;};
    template<class...Ts>using void_t=typename voider<Ts...>::type;
// given `Z<?...>` and `types<Ts...>`, if `Z<Ts...>` is valid, we done.

    template<template<class...>class Z, class types, class=void>
    struct can_apply : std::false_type {};
    template<template<class...>class Z, class...Ts>
    struct can_apply<Z, types<Ts...>, void_t<Z<Ts...>>> : std::true_type {};

    template<template<class...>class Z, class T, class=void>
    struct is_instance_of : std::false_type {};

    template<template<class...>class Z, template<class...>class Y, class... Ts>
    struct is_instance_of<
      Z, Y<Ts...>,
      std::enable_if_t<can_apply< Z, types<Ts...> >{}>
    > : std::is_same< Z<Ts...>, Y<Ts...> > {};
      

    template<template<class...>class Z, class U>
    using is_tbase_of = is_instance_of<Z,U>;
}
using shiny::is_tbase_of;

template <template <class...> class T>
struct quote
{
    template <class... U>
    using type = T<U...>;
};

using QVec = quote<std::vector>;


template <class...> struct S {};
template <class > struct S2 {};

static_assert( !is_tbase_of< std::vector, std::is_integral<int>  >::value, "" );
static_assert(  is_tbase_of< std::vector, std::vector<int>       >::value, "" );
static_assert(  is_tbase_of< QVec::type,  std::vector<int>       >::value, "" );
static_assert( !is_tbase_of< std::vector, S<int, int, int>       >::value, "" );
static_assert( !is_tbase_of< S2, S<int, int, int>       >::value, "" );

// some of this code (the test harness) stolen from http://stackoverflow.com/questions/28854125/how-to-compare-a-template-template-with-a-template-instance/28865203#28865203

int main()
{
}

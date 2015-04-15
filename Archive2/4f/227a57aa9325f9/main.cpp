#include <utility>
#include <type_traits>
#include <iostream>

    // Better name for the type:
    template<bool b>
    using bool_t = std::integral_constant<bool, b>;
    // bundle of types:
    template<class...>struct types{using type=types;};

    // takes a test, and a types<?...> of things to test against it:
    template<template<class...>class Z, class args>
    struct test_lists:std::true_type{};
    template<template<class...>class Z, class...Ts, class...Us>
    struct test_lists<Z,types<types<Ts...>,Us...>>:bool_t<
      Z<Ts...>{} && test_lists<Z, types<Us...>>{}
    >{};

    // takes 0 or more types<?...> and concatenates them:
    template<class...types>
    struct concat_types;
    template<class...types>
    using concat_types_t=typename concat_types<types...>::type;
    template<>
    struct concat_types<>:types<>{};
    template<class...Ts>
    struct concat_types<types<Ts...>>:types<Ts...>{};
    template<class...T0s,class...T1s, class...more>
    struct concat_types<types<T0s...>,types<T1s...>,more...>:
      concat_types_t< types<T0s...,T1s...>, more... >
    {};

    // takes a template Z and and arg, and produces a template
    // equal to Z<Arg, ?...>:
    template<template<class...>class Z, class Arg>
    struct bind_1st {
        template<class...Ts>
        using apply=Z<Arg,Ts...>;
    };

    // takes a template Z and a types<?...> and produces
    // types< Z<?>... >:
    template<template<class...>class Z, class types>
    struct map;
    template<template<class...>class Z, class types>
    using map_t=typename map<Z,types>::type;
    template<template<class...>class Z, class...Ts>
    struct map<Z,types<Ts...>>:types<Z<Ts>...>{};

    // builds a cross product of zero or more types<?...>:
    template<class...types0>
    struct cross_types;
    template<class...types>
    using cross_types_t=typename cross_types<types...>::type;

    // valid degenerate cases:
    template<class...Ts>
    struct cross_types<types<>,Ts...>:types<>{};
    template<>
    struct cross_types<>:types<types<>>{};

    // meat of cross_types:
    template<class T0, class...T0s, class...Us>
    struct cross_types<types<T0,T0s...>, Us...>:
      concat_types_t<
        map_t< bind_1st< concat_types_t, types<T0> >::template apply, cross_types_t<Us...> >,
        cross_types_t< types<T0s...>, Us... >
      >
    {};

    // takes a test Z, and a sequence of types<?...> args
    // tests the cross product of the contents of the args:
    template<template<class...>class Z, class...Args>
    struct test_cross : test_lists<Z, cross_types_t<Args...>> {};

    struct MyClass {
        void f(float x){
            std::cout << x << '\n';
        }
    };
    template<class...Ts>
    std::enable_if_t<
      test_cross<std::is_same, types<MyClass>, types<Ts...>>{}
    >
    myFunc( float x, Ts*... p ) {
      using discard=int[];
      (void)discard{0,((
        p->f(x)
      ),void(),0)...};
    }
    
    template<class T>using identity=T;

int main() {
    map_t< identity, types<int,int,int> > y = types<int,int,int>{};
    map_t<
            bind_1st<
                concat_types_t, types<int>
            >::template apply,
            types< types<int>, types<int> >
        > x = types<types<int,int>,types<int,int>>{};
    (void)x;
    (void)y;
    types<types<int>> z = cross_types_t<types<int>>{};
    (void)z;
    types<types<int>, types<int>> w = cross_types_t<types<int,int>>{};
    (void)w;

    bind_1st< concat_types_t, types<int>>::apply< types<int> > foo = types<int,int>{};
    (void)foo;
    
    types<types<int, int>, types<int,int>> v = cross_types_t<types<int>,types<int,int>>{};
    (void)v;
        
    MyClass a,b,c;
//   myFunc( 3.14, &a, &b, &c, new int ); // does not compile, no overload found
   myFunc( 3.14, &a, &b, &c );
}
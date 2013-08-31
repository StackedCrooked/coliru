    #include <type_traits>

    template<typename T, typename U>
    struct foo {};

    template<template<typename...> class TT, typename T>
    struct is_instantiation_of : std::false_type { };

    template<template<typename...> class TT, typename... Ts>
    struct is_instantiation_of<TT, TT<Ts...>> : std::true_type { };

    template<typename FooType>
    struct bar {
      static_assert(is_instantiation_of<foo, FooType>::value, "failure");
    };

    int main()
    {
        //bar<int> b; // ERROR!
        bar<foo<int, double>> b; // OK!
    }

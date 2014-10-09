#include <tuple>
#include <ratio>
#include <type_traits>

template<int... I>
using make_dimension = std::tuple<std::ratio<I>...>;

using scalar_dimension = make_dimension<0, 0, 0, 0, 0, 0, 0>;
using length_dimension = make_dimension<1, 0, 0, 0, 0, 0, 0>;
using time_dimension = make_dimension<0, 0, 1, 0, 0, 0, 0>;

    template<template<class, class> class, class, class>
    struct tuple_transform; 

    template<template<class, class> class Transform, class...Ts, class...Vs>
    struct tuple_transform<Transform, std::tuple<Ts...>, std::tuple<Vs...>> {
        using type = std::tuple<Transform<Ts, Vs>...>;
    };

    template<class T, class U>
    using subtract_dimensions = typename tuple_transform<std::ratio_subtract, T, U>::type;
    
    using velocity_dimension = subtract_dimensions<length_dimension, time_dimension>;
    
    static_assert(std::is_same<velocity_dimension, make_dimension<1, 0, -1, 0, 0, 0, 0>>::value, "Oops");
    
    int main() {}
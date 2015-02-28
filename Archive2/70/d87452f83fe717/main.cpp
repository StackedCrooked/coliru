#include <utility>
#include <tuple>

using namespace std;


template<typename T, size_t I>
struct annotated_type
{
    using type = T;
    static constexpr size_t index = I;
};


template<typename Current, typename Next, typename Insert, typename=void>
struct shift_t;

template<typename Current, typename Next, typename Insert>
using shift = typename shift_t<Current, Next, Insert>::type;

template<typename Current, typename Next, typename Insert>
struct shift_t< Current, Next, Insert, enable_if_t<(Current::index < Insert::index)> >
{
    using type = Current;
};
template<typename Current, typename Next, typename Insert>
struct shift_t< Current, Next, Insert, enable_if_t<(Current::index == Insert::index)> >
{
    using type = Insert;
};
template<typename Current, typename Next, typename Insert>
struct shift_t< Current, Next, Insert, enable_if_t<(Current::index > Insert::index)> >
{
    using type = Next;
};


template<typename right_extended_tuple, typename left_extended_tuple, typename insert>
struct shift_tuple_helper_t;

template<typename... right_extended, typename... left_extended, typename insert>
struct shift_tuple_helper_t< tuple<right_extended...>, tuple<left_extended...>, insert >
{
    using type = tuple< shift< right_extended, left_extended, insert >... >;
};

template<typename right_extended_tuple, typename left_extended_tuple, typename insert>
using shift_tuple_helper = typename shift_tuple_helper_t<right_extended_tuple, left_extended_tuple, insert>::type;


template<template<typename> class UnaryTypeFunction, typename Tuple>
struct apply_t;

template<template<typename> class UnaryTypeFunction, typename... types>
struct apply_t<UnaryTypeFunction, tuple<types...>>
{
    using type = tuple< UnaryTypeFunction<types>... >;
};

template<template<typename> class UnaryTypeFunction, typename Tuple>
using apply = typename apply_t<UnaryTypeFunction, Tuple>::type;


template<typename AT>
using remove_annotation = typename AT::type;


template<typename Tuple, typename Insert, typename Indices = make_index_sequence< tuple_size<Tuple>::value >>
struct insert_t;

template<typename Tuple, typename InsertType, size_t At>
using insert = typename insert_t<Tuple, annotated_type<InsertType, At>>::type;

template<typename... types, typename Insert, size_t... Indices>
struct insert_t< tuple<types...>, Insert, index_sequence<Indices...> >
{
    using right_extend = tuple<annotated_type<types, Indices>..., Insert>;
    using left_extend = tuple<annotated_type<void, 0>, annotated_type<types, Indices>...>;
    using shifted_tuple = shift_tuple_helper<right_extend, left_extend, Insert >;
    using type = apply<remove_annotation, shifted_tuple>;
};


#include <iostream>
template<typename T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

int main()
{
    using t0 = tuple<int, double, char, bool>;
    print_type< insert<t0, long, 4> >();
}
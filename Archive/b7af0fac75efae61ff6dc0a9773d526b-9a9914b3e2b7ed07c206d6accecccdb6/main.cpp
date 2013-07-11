#include <tuple>
#include <type_traits>

template<unsigned i> struct Element;

template<> struct Element<0> {typedef int type;};
template<> struct Element<1> {typedef float type;};
template<> struct Element<2> {typedef double type;};

template<unsigned N, template<unsigned> class TT, class TupleAcc = std::tuple<>>
struct tuple_over{
  using tt_type = typename TT<N-1>::type;
  // since we're going from high to low index,
  // prepend the new type, so the order is correct
  using cat_type = decltype(std::tuple_cat(std::declval<std::tuple<tt_type>>(), std::declval<TupleAcc>()));
  using type = typename tuple_over<N-1, TT, cat_type>::type;
};

template<template<unsigned> class TT, class Tuple>
struct tuple_over<0, TT, Tuple>{ using type = Tuple; };

int main()
{
    static_assert(
        std::is_same<
            tuple_over<3, Element>::type,
            std::tuple<int, float, double>
        >::value, "!");
}

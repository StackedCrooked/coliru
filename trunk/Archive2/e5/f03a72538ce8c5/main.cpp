#include <ratio>
#include <tuple>

template<int... I>
using make_dimension = std::tuple<std::ratio<I>...>;

using scalar_dimension = make_dimension<0, 0, 0, 0, 0, 0, 0>;
using length_dimension = make_dimension<1, 0, 0, 0, 0, 0, 0>;
using time_dimension = make_dimension<0, 0, 1, 0, 0, 0, 0>;



template<typename L, typename R, template<class,class> class F, typename = std::tuple<>>
struct transform;

template<template<class,class> class F, typename Result>
struct transform< std::tuple<>, std::tuple<>, F, Result >
{
    using type = Result;
};

template<typename LH, typename... LT,
         typename RH, typename... RT,
         template<class,class> class F,
         typename... Result >
struct transform< std::tuple<LH, LT...>,
                  std::tuple<RH, RT...>,
                  F,
                  std::tuple<Result...> >
    : transform< std::tuple<LT...>, std::tuple<RT...>, F, std::tuple<Result..., typename F<LH, RH>::type> >
{};



using t0 = transform<length_dimension, length_dimension, std::ratio_add>::type;
using t1 = transform<length_dimension, length_dimension, std::ratio_multiply>::type;

using t2 = transform<length_dimension, time_dimension, std::ratio_add>::type;
using t3 = transform<length_dimension, time_dimension, std::ratio_multiply>::type;


#include <iostream>

template<typename T>
void print_type()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

int main()
{
    print_type<t0>();
    print_type<t1>();
    print_type<t2>();
    print_type<t3>();
}
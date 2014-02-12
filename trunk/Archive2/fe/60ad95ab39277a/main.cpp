#include <type_traits>

template<class> struct B1 { };
template<class> struct B2 { };

struct D1 : B1<void>           { };
struct D2 : B1<void>, B2<void> { };


struct temp_deduct_call_4 {};
struct temp_deduct_call_5 {};

template<template<class> class TT, class T>
temp_deduct_call_4 func (TT<T>);

temp_deduct_call_5 func (...);

int
main (int argc, char *argv[])
{
  
  static_assert (
    std::is_same<temp_deduct_call_4, decltype (func (D1 {}))>::value,
    "violates [temp.deduct.call]/4; "

    "`B1<void>` is a base of `D1`, func (TT<T>) should be called!"
  );

  static_assert (
    std::is_same<temp_deduct_call_5, decltype (func (D2 {}))>::value,
    "violates [temp.deduct.call]/5; "

    "func(TT<T>) can be called with both `B1<void>` and `B2<void>` "
    "which are both bases of D2, this causes ambigiuity and `func(...)` "
    "should be called!"
  );
}
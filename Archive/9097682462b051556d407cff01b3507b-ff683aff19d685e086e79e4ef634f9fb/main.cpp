template<template<typename T1, typename T2> class trait, typename U, typename V, int B = true>
void test_binary_trait_cv()
{
  static_assert(trait<U, V>::value == B, "");
  static_assert(trait<U, const V>::value == B, "");
  static_assert(trait<U, volatile V>::value == B, "");
  static_assert(trait<U, const volatile V>::value == B, "");
  static_assert(trait<const U, V>::value == B, "");
  static_assert(trait<const U, const V>::value == B, "");
  static_assert(trait<const U, volatile V>::value == B, "");
  static_assert(trait<const U, const volatile V>::value == B, "");
  static_assert(trait<volatile U, V>::value == B, "");
  static_assert(trait<volatile U, const V>::value == B, "");
  static_assert(trait<volatile U, volatile V>::value == B, "");
  static_assert(trait<volatile U, const volatile V>::value == B, "");
  static_assert(trait<const volatile U, const V>::value == B, "");
  static_assert(trait<const volatile U, volatile V>::value == B, "");
  static_assert(trait<const volatile U, const volatile V>::value == B, "");
}
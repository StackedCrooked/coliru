struct S { int data; };

template<typename T, int T::* p> struct C {};

template<template<typename A, decltype(&A::data)> class T, typename U>
using make_type = T<U, &U::data>;

int main() {
  make_type<C, S> blah;
}
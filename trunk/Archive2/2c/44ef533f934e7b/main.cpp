template <typename T>
struct S1 { };

template <template <typename> class TT>
struct S2 { };

template <template<template<class> class > class TTT>
struct S3 { };

int main() {
  S3<S2> s3;
}
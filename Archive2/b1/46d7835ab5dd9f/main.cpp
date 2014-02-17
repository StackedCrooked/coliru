#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;
 
template<typename T> struct S;
 
struct Z {
  static constexpr unsigned int n = 0;
 
  template<typename T>
  using replace = T;
};
 
// Dummy class, just to help debug!
struct I {
  static constexpr unsigned int n = 100;
};
 
template<typename T>
struct S {
  static constexpr unsigned int n = T::n + 1;
 
  template<typename U, typename V = T>
  using replace = S<typename V::template replace<U>>;
};
 
template<typename T>
using succ = S<T>;
 
using _0 = Z;
using _1 = succ<_0>;
using _2 = succ<_1>;
 
int main() {
 
  // If substituon works, should display 102, and would
  // enable summation
  cout << _2::replace<I>::n << endl;
 
  return EXIT_SUCCESS;
};

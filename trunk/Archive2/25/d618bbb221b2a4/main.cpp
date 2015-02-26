template <typename T>
int f();

template <typename T>
struct S {
  template <typename U>
  static int f();

  template <class U>
  using u = decltype(f<U>());

  using t = u<T>;
};

#include <iostream>

S<int>::t main() { std::cout << "hello world\n"; }
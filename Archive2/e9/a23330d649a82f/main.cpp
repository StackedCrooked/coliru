#include <iostream>

namespace N {
  struct S {};
}

template<class T>
void g(T&&) {
    std::cout << "generic\n";
}

template<class T>
void f(T&& value) {
    g(value); // search namespaces where `T` belongs,
              // no matter if they have been declared yet, or not
}

namespace N {
  void g (N::S) {
    std::cout << "overload\n";
  }
}

int main() {
  using S = N::S;

  f(S{});

  return 0;
}
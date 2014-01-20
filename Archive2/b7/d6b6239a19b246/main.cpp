#include <iostream>
#include <type_traits>

typedef int T;

struct A {
  A(T) {}
};

struct B {
  B(T) {}
};

struct C {
  C(A const&) { std::cout << "C(A)\n"; }
  C(B const&) { std::cout << "C(B)\n"; }
  template <typename U, typename=typename std::enable_if<
    !std::is_base_of<A,typename std::decay<U>::type>::value &&
    std::is_convertible<U&&, A>::value>::type
  > C(U&& u) : C(A(u)) {}
};

int main() {
  C a(A(42));
  C b(B(42));
  C c(42);
  B d(13);
  C e(d);
}

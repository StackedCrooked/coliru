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
  {
    std::cout << "rvalue A: ";
    C c(A(42));
  }
  {
    std::cout << "rvalue B: ";
    C c(B(42));
  }
  {
    std::cout << "lvalue A: ";
    A a(13);
    C c(a);
  }
  {
    std::cout << "lvalue B: ";
    B b(13);
    C c(b);
  }
  {
    std::cout << "rvalue T: ";
    C c(42);
  }
  {
    std::cout << "lvalue T: ";
    T t{};
    C c(t);
  }
}

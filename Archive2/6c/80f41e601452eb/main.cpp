#include <iostream>
#include <type_traits>

struct T {};

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
  > C(U&& u) : C(A{std::forward<U>(u)}) {}
};

int main() {
  {
    std::cout << "rvalue A: ";
    C c{A{T{}}};
  }
  {
    std::cout << "rvalue B: ";
    C c{B{T{}}};
  }
  {
    std::cout << "lvalue A: ";
    A a{T{}};
    C c{a};
  }
  {
    std::cout << "lvalue B: ";
    B b{T{}};
    C c{b};
  }
  {
    std::cout << "rvalue T: ";
    C c{T{}};
  }
  {
    std::cout << "lvalue T: ";
    T t{};
    C c{t};
  }
}

#include <iostream>
#include <typeinfo>

struct A {
  A (int) {}
};
struct B {
  B (A) {}
  B(B const &) = delete;
};
int main () {
  int i = 1;
  B b = A(i); // (1)
  std::cout << typeid(b).name() << std::endl;
  return 0;
}

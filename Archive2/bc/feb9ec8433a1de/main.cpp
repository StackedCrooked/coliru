#include <iostream>
#include <typeinfo>

struct A {
  A (int) {}
};
struct B {
  B (A) { std::cout << "direct" << std::endl; }
  B(B const&) { std::cout << "copy" << std::endl; }
  B(B&&) { std::cout << "move" << std::endl; }
};
int main () {
  B b = A(1); // (1)
  return 0;
}

#include <iostream>
#include <typeinfo>

struct A {
  A (int) {}
};
struct B {
  B(A) { std::cout << "direct" << std::endl; }
  B(B const&) = delete;
  B(B&&) { std::cout << "move" << std::endl; }
};
int main () {
  A a{1};
  B b = a; // (1)
  return 0;
}

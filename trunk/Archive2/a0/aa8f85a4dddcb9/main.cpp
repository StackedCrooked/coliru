#include <iostream>

struct A {
  A (int) {}
};

struct B {
  B() = default;
  B(B const&) = delete;
  B(A) {}
};

int main () {
  // this fails...
  // B b = A(1);
  
  // ...but this is ok
  B b;
  b = { A(1) };
  b = A(1);
  b = B(A(1));
  b = { A(1) };
  b = { B(A(1)) };
  
  std::cout << "yay" << std::endl;
  return 0;
}

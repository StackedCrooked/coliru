#include <iostream>

struct A {
  virtual void f() { std::cout << "A::f()" << std::endl; }    
};

struct B : A {
  void f() override { std::cout << "B::f()" << std::endl; }
};

void f() {
  A *b = new B;
  b->f(); // Calls B::f
  b->A::f(); // Call A::f
}

int main() {
  f();
}
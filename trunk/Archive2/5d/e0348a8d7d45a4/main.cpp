#include <iostream>

struct A {
  void foo() { std::cout << "A::foo" << std::endl; }
};

struct B {
  void foo() { std::cout << "B::foo" << std::endl; }  
};

struct C : public A, B {};

void callFoo(C &c) {
  c.A::foo();
  c.B::foo();
}

int main(void) {
  C c;
  callFoo(c);
}

#include <iostream>

class A {
public:
  A() { std::cout << "const A" << std::endl;}
  ~A() {
    std::cout << "dest A" << std::endl;
  }
};

class B : public A {
public:
  B() { std::cout << "const B" << std::endl;}
  virtual ~B() {
    std::cout << "dest B" << std::endl;
  }
};

class C : public B {
public:
  C() { std::cout << "const C" << std::endl;}
  ~C() {
    std::cout << "dest C" << std::endl;
  }
};

int main() {
  B *c = new C();
  delete c;

  return 0;
}
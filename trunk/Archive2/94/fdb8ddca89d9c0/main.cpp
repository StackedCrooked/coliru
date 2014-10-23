#include <iostream>

struct A
{
  virtual void f() { std::cout << "A\n"; }
};

struct B : A
{
  void f() override { std::cout << "B\n"; }
};

int main()
{
  B b;
  b.A::f();
}
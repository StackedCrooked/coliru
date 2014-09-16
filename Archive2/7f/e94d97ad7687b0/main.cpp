#include <iostream>

class A { public: static void f() { std::cout << "Base class A\n"; } };

class B : public A {
public:
  class A {
  public:
    static void f() { std::cout << "Nested class A\n"; }
  };

  B() { A::f(); ::A::f(); }
};

int main()
{
    B b;
}
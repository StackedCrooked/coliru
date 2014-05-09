#include <iostream>
class B {
public:
    void foo() { std::cout << "B::foo()" << '\n'; }
};

class D : public B {
public:
    void foo() { std::cout << "D::"; B::foo(); }
};

int main() {
  D d;
  d.foo();
}
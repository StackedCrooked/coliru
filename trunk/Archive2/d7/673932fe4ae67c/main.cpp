#include <iostream>
#include <string>
#include <vector>


class A {
  public:
    A(int){ }
};

class B : public A {
  public:
    using A::A;
};

int main() {
    B b{1};
}

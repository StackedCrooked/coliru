#include <iostream>

class foo {
  public:
    void fun() const { std::cout << "foo:fun()" << std::endl; }
};

int main() {
    foo f;
    f.foo::fun();
    return 0;
}
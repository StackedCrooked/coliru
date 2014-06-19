#include <iostream>

struct foo {
    void virtual fun() const { std::cout << "foo::fun()" << std::endl; }
};
struct bar : foo {
    void fun() const override { std::cout << "bar::fun()" << std::endl; }
};

auto main() -> int {
  bar b;
  foo *f = &b;
  f->fun();
  f->foo::fun();
}

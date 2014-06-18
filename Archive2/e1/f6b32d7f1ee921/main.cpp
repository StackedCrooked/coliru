#include <iostream>

struct foo {
    void fun() const { std::cout << "foo::fun()" << std::endl; }
};

auto main() -> int {
  foo f;
  f.fun();
  f.foo::fun();
  
  return 0;
}
#include <iostream>

struct Foo {
    int &bar;

    Foo(int& bar): bar(bar) { }
};

int main () {
  int bar = 42;
  Foo foo(bar);
  std::cout << foo.bar;  // prints 0
  return 0;
}
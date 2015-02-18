#include <iostream>

struct Foo {
  static void bar() {}
  void bar2() {}
};

using baz = decltype(&Foo::bar);

void foo() { std::cout << "foo\n"; }

int main() 
{
    baz b = foo;
    b();
}
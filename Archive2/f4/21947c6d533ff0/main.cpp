#include <iostream>

struct Foo {
  static void bar() {}
};

using baz = decltype(&Foo::bar);

void foo() { std::cout << "foo\n"; }

int main() 
{
    baz b = foo;
    b();
}
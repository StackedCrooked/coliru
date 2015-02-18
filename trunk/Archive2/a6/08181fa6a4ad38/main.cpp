#include <iostream>

struct Foo {
  static void bar() { std::cout << "bar\n"; }
};

constexpr auto baz = &Foo::bar; 

void test() { baz(); }

int main() 
{
    test();
}
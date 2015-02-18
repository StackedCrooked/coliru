#include <iostream>

struct Foo {
  static void bar() { std::cout << "bar\n"; }
};

auto baz = Foo::bar; //Does not compile

void test() { baz(); } //Goal is that this should compile

int main() 
{
    test();
}
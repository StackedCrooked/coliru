#include <iostream>

struct A{ void foo(){ std::cout << "foo()" << std::endl; } };

struct B : A{ };

struct C : A{ };

B *b = new B();

C *c = reinterpret_cast<C*>(b);

int main(){ c -> foo(); }
#include <iostream>

struct A{ void foo(){ std::cout << "foo()" << std::endl; } };

struct D{ void bar(){ std::cout << "bar()" << std::endl; } };

struct B : A, D{ };

struct C : A{ };

B *b = new B();

C *c = reinterpret_cast<C*>(b);

int main(){ c -> foo(); }
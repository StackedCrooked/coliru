#include <iostream>

struct A{ int a; };

// void f( const A & a = A() ){ /*a.a = 42;*/ std::cout << "it works" << std::endl; }
// Will not compile:
void f( A & a = A() ){ /*a.a = 42;*/ std::cout << "it works" << std::endl; }

int main()
{
  f();
  return 0;
}
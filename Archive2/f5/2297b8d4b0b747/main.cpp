#include <iostream>
#include <typeinfo>

struct A{};

template<typename T> void foo(T* x)
{ std::cout << "foo<" << typeid(T).name() << ">(T*)\n"; }

void foo(A x)
{ std::cout << "foo(A)\n"; }

void foo(int x)
{ std::cout << "foo(int)\n"; }

void foo(double x)
{ std::cout << "foo(double)\n"; }

int main()
{
    foo(42);        // matches foo(int) exactly
    foo(42.0);      // matches foo(double) exactly
    foo(A());  // matches foo<T>(T*) with T = char    
    foo("abcdef");  // matches foo<T>(T*) with T = char
    return 0;
}
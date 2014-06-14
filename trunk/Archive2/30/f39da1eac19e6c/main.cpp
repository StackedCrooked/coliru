#include <stdio.h>


// Excercise from the book "Advanced C++ Metaprogramming" by Gennaro


// GIVEN:

template<typename T>
void f(T) { puts("T"); }
struct Base {};


// TODO: write overload that works for Base or derived classes


// my initial attempt (which does not work for derived classes)
void f(Base)
{
    puts("Base or derived");
}


int main()
{
    struct Derived : Base {};

    Base base;
    Derived derived;

    // Test
    f(1);       // OK, calls template f
    f(base);    // OK, calls f(Base)
    f(derived); // WRONG: calls template f
}

#include <iostream>

enum class X : int { A = 42, B = 21 };

void __attribute__((noinline)) foo(X* x, int* i)
{
    *x = X::B;       // sets x to 21
    std::cout << *i; // should print 21, right?
}

int main()
{
    X x = X::A;
    foo(&x, reinterpret_cast<int*>(&x));
}
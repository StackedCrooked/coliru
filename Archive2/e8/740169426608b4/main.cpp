#include <new>
#include <iostream>
struct X { int i; };
int main()
{
    void* buf = operator new(sizeof(X));
    ((X*)buf)->i = 42;
    new (buf) X;
    std::cout << ((X*)buf)->i;
}

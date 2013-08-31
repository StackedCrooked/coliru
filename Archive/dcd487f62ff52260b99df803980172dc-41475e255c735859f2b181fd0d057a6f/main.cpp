#include <iostream>

template <unsigned N, typename T = int (*) (const char (*)[N])>
int foo (T* ptr)
{
    return ptr(&"good");
}

int bar (const char (*x)[5]) {
    std::cout << *x << "\n";
    return 0;
}

int main ()
{
    return foo<5>(bar);
}
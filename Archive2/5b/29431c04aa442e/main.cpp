#include <iostream>

template<typename T>
void foo(T) { std::cout << 1; }

template<typename T>
void foo(T*) { std::cout << 2; }

int main()
{
    foo((int*)0);
    foo(0);
}

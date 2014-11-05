#include <iostream>

template <typename T>
struct X {};

template <class T>
void foo(T) {}

template <class T>
void foo(const X<T>&) { std::cout << "more specialized" << std::endl; }

int main()
{
    foo(X<int>{});
}

#include <iostream>

template<typename T>
void foo(const T*) // #1: T = int => foo(const int*)
{
    std::cout << "Overload #1";
}

template<typename T>
void foo(const T&) // #2: T = int* => foo(const int*&)
{
    std::cout << "Overload #2";
}

int main()
{
    int* p = nullptr;
    foo(p);
}

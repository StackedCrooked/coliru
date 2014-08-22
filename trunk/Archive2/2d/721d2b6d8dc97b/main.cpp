#include <iostream>

template<typename T>
void foo(const T*)
{
    std::cout << "Overload #1";
}

template<typename T>
void foo(const T&)
{
    std::cout << "Overload #2";
}

int main()
{
    int* p = nullptr;
    foo(p);
}

#include <iostream>

template<typename T>
void foo(const T*) // #1: T = int => foo(const int*)
                   // Simple text replacement would suggest this...
{
    std::cout << "Overload #1";
}

template<typename T>
void foo(const T&) // #2: T = int* => foo(const int*&)
                   // But this one is picked instead
{
    std::cout << "Overload #2";
}

int main()
{
    int* p = nullptr;
    foo(p);
}

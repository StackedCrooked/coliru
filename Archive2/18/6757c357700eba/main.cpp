#include <iostream>

template<typename T>
void foo(T const*) // #1: T = int => foo(int const*)
                   // This requires a const conversion...
{
    std::cout << "Overload #1";
}

template<typename T>
void foo(T const&) // #2: T = int* => foo(int* const&)
                   // ...while this doesn't!
{
    std::cout << "Overload #2";
}

int main()
{
    int* p = nullptr;
    foo(p);
}

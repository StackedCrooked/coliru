#include <iostream>

template<typename T, unsigned N>
T(*identity(T(&a)[N]))[N] { return &a; }

int main()
{
    int a[] = {1, 2};
    for (auto x : *identity(a))
        std::cout << x << '\n';
}
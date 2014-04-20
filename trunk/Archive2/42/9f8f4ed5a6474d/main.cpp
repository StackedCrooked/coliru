#include <iostream>

struct T
{
    int x;
};

int main()
{
    std::cout << sizeof(decltype(T::x)) << '\n';
}
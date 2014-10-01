#include <iostream>

struct T
{
    static int x;
};

int T::x;   // no initialisation!

int main()
{
    std::cout << T::x << std::endl; // no problem!
}
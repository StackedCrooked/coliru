#include <iostream>

struct T
{
    static int x;
};

//int T::x;   // no definition!

int main()
{
    std::cout << T::x << std::endl; // a problem!
}
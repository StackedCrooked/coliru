#include <iostream>

struct A {};

struct B : A {};

int main()
{
    B b;
    A* ptr = 0;

    try
    {
        throw b;
    }
    catch (A& a)
    {
        ptr = &a;
    }

    std::cout << ptr << std::endl;

    return 0;
}

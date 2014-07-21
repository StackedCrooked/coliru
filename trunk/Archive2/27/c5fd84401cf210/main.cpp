#include <iostream>

int global_x = 0;
struct X { int a = (global_x++) ? 1 : 2;};

int main()
{
    X x;
    std::cout << global_x << std::endl;
}
#include <iostream>

int main()
{
    std::cout.tie(&std::cout);
    std::cout << 123;
}
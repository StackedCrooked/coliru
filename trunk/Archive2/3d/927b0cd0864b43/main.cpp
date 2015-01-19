#include <cmath>
#include <iostream>
#include <typeinfo>

int main()
{
    std::cout << typeid(decltype(std::sqrt(-1))).name() << std::endl;
}

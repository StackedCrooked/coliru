#include <iostream>

int main()
{
    std::cout << typeid(true ? 1 : 1.0).name() << std::endl;
    std::cout << typeid(false ? 1 : 1.0).name() << std::endl;
    return 0;
}
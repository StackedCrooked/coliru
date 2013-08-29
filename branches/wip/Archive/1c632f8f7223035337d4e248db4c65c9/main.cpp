#include <cstdlib>
#include <iostream>

int main()
{
    std::cout << __LINE__ << std::endl;
    system("find /");
    std::cout << __LINE__ << std::endl;
    std::cout << __LINE__ << std::endl;
    std::cout << __LINE__ << std::endl;
}
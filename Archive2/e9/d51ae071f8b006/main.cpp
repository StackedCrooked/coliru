#include <iostream>
#include <iomanip>

int main()
{
    int a;
    std::cout << std::hex << std::right << std::setw(sizeof(void*)) << &a << std::endl;
    std::cout << std::hex << std::right << std::setw(2*sizeof(void*)) << &a << std::endl;
}

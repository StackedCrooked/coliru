#include <iostream>
#include <type_traits>

int data[][3] = {
    { 1, 2, 3 },
    { 4, 5, 6 }
};


std::array< 2, std::array<3, int> > arr;

int main()
{
    std::cout << std::extent<decltype(data), 0>::value << std::endl;
    std::cout << std::extent<decltype(data), 1>::value << std::endl;
}
#include <iostream>
#include <type_traits>
 
int main()
{
    std::cout << std::extent<int[3]>::value << '\n';
    std::cout << std::extent<int[3][4]>::value << '\n';
    std::cout << std::extent<int[3][4], 1>::value << '\n';
    std::cout << std::extent<int[3][4], 2>::value << '\n';
    std::cout << std::extent<int[]>::value << '\n';
}
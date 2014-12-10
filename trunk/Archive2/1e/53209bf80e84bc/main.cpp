#include <array>
#include <iostream>

int main()
{
    const std::array<int, 3> arr { 1, 2, 3 };
    
    std::array<int, arr.size()> arr2;
    
    std::cout << arr.size() << arr2.size() << std::endl;
}
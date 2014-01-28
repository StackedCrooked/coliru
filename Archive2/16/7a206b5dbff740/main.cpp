#include <iostream>
#include <array>
 
int main()
{
    std::array<int, 3> arr;
 
    // set values:
    std::get<0>(arr) = 1;
    std::get<1>(arr) = 2;
    std::get<2>(arr) = 3;
 
    // get values:
    std::cout << "(" << std::get<0>(arr) << ", " << std::get<1>(arr)
              << ", " << std::get<2>(arr) << ")\n";
}
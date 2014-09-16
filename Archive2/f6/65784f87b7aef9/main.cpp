#include <algorithm>
#include <iostream>

int main()
{
    const int len = 10;
    int intArray[len] = {5, 6, 4, 1, 3, 10, 15, 13, 2, 7};
    std::reverse(std::begin(intArray), std::end(intArray));
    
    for (auto&& e : intArray)
        std::cout << e << ", ";
}

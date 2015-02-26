#include <iostream>
#include <algorithm>
#include <array>
 
int main()
{
    std::array<int, 11> arr{ 5, 9, 2, 1, 4, 8, 7, 0, -1, 3, 6 };
 
    std::sort(arr.begin(), arr.end());
    std::cout << *std::lower_bound(arr.begin(), arr.end(), 5) << std::endl;
}

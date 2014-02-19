#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> v = { 3, 9, 1, 4, 2, 5, 9 };
 
    auto result = std::minmax_element(v.begin(), v.end());
    std::cout << "min element at: " << (result.first - v.begin()) << '\n';
    std::cout << "max element at: " << (result.second - v.begin()) << '\n';
}
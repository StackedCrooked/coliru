#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> v = { 3, 9, 10, 4, 305, 5, 9 };
 
    auto result = std::minmax_element(v.begin(), v.end());
    
    std::cout << "min element is: " << (result.first[0])  << '\n';
    std::cout << "min element at: " << (result.first - v.begin()) << '\n';
    std::cout << "max element is: " << (result.second[0])  << '\n';
    std::cout << "max element at: " << (result.second - v.begin()) << '\n';
}
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
 
static bool abs_compare(int a, int b)
{
    return (std::abs(a) < std::abs(b));
}
 
int main()
{
    std::vector<int> v{ 3, 1, -14, 1, 5, 9 }; 
    std::vector<int>::iterator result;
 
    result = std::max_element(v.begin(), v.end());
    std::cout << "max element at: " << std::distance(v.begin(), result) << '\n';
 
    result = std::max_element(v.begin(), v.end(), abs_compare);
    std::cout << "max element (absolute) at: " << std::distance(v.begin(), result);
}
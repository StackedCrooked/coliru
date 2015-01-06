#include <algorithm>
#include <array>
#include <iostream>
 
int main()
{
    std::array<int, 9> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
 
    auto is_even = [](int i){ return i % 2 == 0; };
    std::cout.setf(std::ios_base::boolalpha);
    std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << ' ';
 
    std::partition(v.begin(), v.end(), is_even);
    std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << ' ';
 
    std::reverse(v.begin(), v.end());
    std::cout << std::is_partitioned(v.begin(), v.end(), is_even);
}
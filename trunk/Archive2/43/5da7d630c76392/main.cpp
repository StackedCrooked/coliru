#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
 
bool is_even(int i) { return i % 2 == 0; }
 
int main()
{
    std::vector<int> v;
    for (int i = 0; i < 10; ++i) v.push_back(i);
 
    std::cout << "Original vector:\n    ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
 
    // Partition the vector
    std::vector<int>::iterator p =
        std::partition(v.begin(), v.end(), std::ptr_fun(is_even));
 
    std::cout << "\nPartitioned vector:\n    ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nBefore partition:\n    ";
    std::copy(v.begin(), p,       std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nAfter partition:\n    ";
    std::copy(p,         v.end(), std::ostream_iterator<int>(std::cout, " "));
}
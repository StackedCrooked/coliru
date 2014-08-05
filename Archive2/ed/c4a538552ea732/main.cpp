#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
 
bool is_even(int i) { return i  != 5; }
 
int main()
{
    std::vector<int> v{ 1,2,3,5,5,3,2,1,5,5
    } ;
 
    std::cout << "Original vector:\n    ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
 
    // Partition the vector
    std::vector<int>::iterator p =
       std::stable_partition(v.begin(), v.end(), std::ptr_fun(is_even));
 
    std::cout << "\nPartitioned vector:\n    ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nBefore partition:\n    ";
    std::copy(v.begin(), p,       std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nAfter partition:\n    ";
    std::copy(p,         v.end(), std::ostream_iterator<int>(std::cout, " "));
}
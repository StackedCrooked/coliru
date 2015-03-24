#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> v{3, 2, 4, 1, 5, 9};
 
    std::vector<int>::iterator result = std::min_element(std::begin(v), std::end(v));
    std::cout << "min element at: " << std::distance(std::begin(v), result);
}
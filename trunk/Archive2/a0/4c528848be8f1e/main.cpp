#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
 
int main()
{
    //int n1 = 3;
    //int n2 = 5;
 
    std::vector<int> v{1, 2, 3, 4};
 
    auto result1 = std::find_if(std::begin(v), std::end(v), [](int x){return (x%2) == 0;});
    auto result2 = std::find_if_not(std::begin(v), std::end(v), [](int x){return (x%2) == 0;});
 
    if (result1 != std::end(v)) {
        std::cout << "v contains: " << *result1 << '\n';
    } else {
        std::cout << "v does not contain: " << "even number" << '\n';
    }
 
    if (result2 != std::end(v)) {
        std::cout << "v contains: " << *result2 << '\n';
    } else {
        std::cout << "v does not contain: " << "odd number" << '\n';
    }
}
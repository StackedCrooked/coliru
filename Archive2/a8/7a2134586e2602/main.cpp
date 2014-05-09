#include <iostream>
#include <algorithm>
#include <vector>
 
int main()
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
 
    std::cout << "initially, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
 
    std::make_heap(v.begin(), v.end());
 
    std::cout << "after make_heap, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
 
    while (!v.empty())
    {    
        auto largest = v.front();
        std::pop_heap(v.begin(), v.end()); v.pop_back();
        std::cout << "largest element: " << largest << '\n';
    }

    std::cout << "after removing the largest element, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
}
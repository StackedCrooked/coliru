#include <iostream>
#include <algorithm>
#include <vector>
 
int main()
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    std::vector<int> v2;
    
    std::cout << "initially, v: ";
    for (auto& i : v) { std::cout << i << ' '; }
    std::cout << std::endl;
 
    std::make_heap(v.begin(), v.end());
 
    std::cout << "after make_heap, v: ";
    for (auto& i : v) { std::cout << i << ' '; }
    std::cout << std::endl;
    
    v2 = v;
    while (!v2.empty())
    {    
        auto largest = v2.front();
        std::pop_heap(v2.begin(), v2.end()); v2.pop_back();
        std::cout << "largest element: " << largest << '\n';
    }
    
    for (auto& each : v)
    {
        v2.emplace_back(each);
        std::push_heap(v2.begin(), v2.end());
    }
    
    std::cout << "Build via std::push_heap: ";
    for (auto& i : v2) { std::cout << i << ' '; }
    std::cout << std::endl;
    
    
    while (!v2.empty())
    {
        auto largest = v2.front();
        std::pop_heap(v2.begin(), v2.end()); v2.pop_back();
        std::cout << "largest element: " << largest << '\n';
    }
}

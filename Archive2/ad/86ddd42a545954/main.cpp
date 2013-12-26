#include <iostream>
#include <algorithm>
#include <vector>
 
int main()
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
 
    std::make_heap(v.begin(), v.end(),std::less<int>());
 
    std::cout << "v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
 
    std::pop_heap(v.begin(), v.end()); // moves the largest to the end
 
    std::cout << "after pop_heap: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
 
    int largest = v.back();
    v.pop_back();  // actually removes the largest element
    std::cout << "largest element: " << largest << '\n';
 
    std::cout << "heap without largest: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
}
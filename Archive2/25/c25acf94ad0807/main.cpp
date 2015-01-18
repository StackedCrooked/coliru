#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <list>
#include <forward_list>

int main()
{
    std::list<int> input = { 0, 0, 1, 1, 2, 22, 3, 33, 99 };
    std::vector<int> a = { 1, 2, 3 };
    std::forward_list<int> b = { 4, 5, 6, 7, 8 };    

    auto mid = std::copy(std::begin(a), std::end(a), std::begin(input));
    std::copy(std::begin(b), std::end(b), mid);
    
    for (auto x : input) { std::cout << x << " "; }
}
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

int main()
{
    std::vector<int> input = { 0, 0, 1, 1, 2, 22, 3, 33, 99 };
    std::vector<int> a = { 1, 2, 3 };
    std::vector<int> b = { 4, 5, 6, 7, 8 };    

    std::copy(std::begin(a), std::end(a), std::begin(input));
    std::copy(std::begin(b), std::end(b), std::begin(input) + a.size());
    
    for (auto x : input) { std::cout << x << " "; }
}
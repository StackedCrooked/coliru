#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<std::vector<int> > vv { 
        { 1, 2, 3},
        { 2, 3, 4},
        { 3, 4, 5},
        { 4, 5, 6},
        { 5, 6, 7} };

    for (auto a : vv)
        std::cout 
            << std::boolalpha 
            << (std::find_if(begin(vv), end(vv), [&](std::vector<int>& i) { return i == a; }) - begin(vv)) 
            << "\n";
    for (auto a : vv)
        std::cout 
            << std::boolalpha 
            << (std::find(begin(vv), end(vv), a) - begin(vv)) 
            << "\n";
}

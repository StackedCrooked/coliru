#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v { 1, 2, 3, 4, 5,  6, 7, 8,  9 }; 
    auto p = std::mismatch (v.cbegin (), v.cend (), v.cbegin ());
    std::cerr << (p.first == v.cend ()) << ", " << (p.second == v.cend ()) << std::endl;
}

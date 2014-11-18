#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v1 { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 
    std::vector <int> v2 { 2, 3, 4, 5, 6, 7, 8, 9, 9 }; 
    auto p = std::mismatch (v1.cbegin (), v1.cend (), v2.cbegin (), [] (int a, int b) { return a < b; });
    std::cerr << *p.first << ", " << *p.second << std::endl;
}

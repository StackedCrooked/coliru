#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
 
int main() 
{
    std::vector<int> v = { 3, 1, 4 };
    auto vi = std::begin(v);
    std::cout << *vi << '\n'; 
 
    int a[3] = { -5, 10, 15 };
    std::sort(std::begin(a), std::end(a));
    auto ai = std::begin(a);
    std::cout << *ai << '\n';
}
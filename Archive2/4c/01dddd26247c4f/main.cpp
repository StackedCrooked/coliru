#include <iostream>
#include <unordered_set>
#include <vector>

int main()
{
    auto v = std::vector<int>{1, 2, 2, 3, 1};    
    auto s = std::unordered_set<int>(begin(v), end(v));    
    std::cout << s.size();
}
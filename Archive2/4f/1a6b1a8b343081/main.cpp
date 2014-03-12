#include <iostream>
#include <unordered_set>
#include <algorithm>

int main()
{
    std::unordered_set<int> needles {1, 2, 3};
    std::unordered_set<int> hay {1, 4, 5, 3, 2};
    
    size_t found =
        std::accumulate(needles.cbegin(), needles.cend(), 0,
             [&hay](int n, int elem) { return n + hay.count(elem); });
    
    std::cout << (found == needles.size());  // 1
}
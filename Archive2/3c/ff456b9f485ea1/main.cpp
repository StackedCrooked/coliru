#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    auto v = std::vector<int> { 1, 2, 3 };
    auto rit = std::find(v.rbegin(), v.rend(), 3);
    if (rit != v.rend()) {
        auto idx = std::distance(begin(v), rit.base()) - 1;
        std::cout << idx;
    } else
        std::cout << "not found!";
}
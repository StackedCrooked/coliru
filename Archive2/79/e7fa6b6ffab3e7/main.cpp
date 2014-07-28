#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    auto v = std::vector<int> { 1, 2, 3 };
    auto it = std::prev(std::find(v.rbegin(), v.rend(), 3).base());
    auto idx = std::distance(begin(v), it);
    std::cout << idx;
}

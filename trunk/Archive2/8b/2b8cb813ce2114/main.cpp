#include <vector>
#include <algorithm>
#include <iostream>
int main()
{
    std::vector<int> vert{4, 2, 6, 6, 3, 7};
    std::transform(vert.begin(), vert.end(), vert.begin(), [] (int x) { return x * 10; });
    for (auto const& x : vert)
        std::cout << x << " ";
}
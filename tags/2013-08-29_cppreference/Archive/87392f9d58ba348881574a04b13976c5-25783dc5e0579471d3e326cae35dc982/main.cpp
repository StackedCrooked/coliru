#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    auto const n = 2;
    auto const pred = [](int i){ return i > 0; };
    auto v = std::vector<int>{ 0, 0, 3, 0, 2, 4, 5, 0, 7 };

    std::stable_partition(v.begin(), v.end(), pred);
    auto const nth_match = std::next(v.begin(), n - 1);
    std::cout << *nth_match << '\n';               // prints 2
}
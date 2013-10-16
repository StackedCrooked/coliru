#include <string>
#include <cctype>
#include <algorithm>
#include <functional>
#include <iostream>
 
int main()
{
    std::vector<int> ints1({1, 2, 3, 4, 5});
    std::vector<int> ints2({2, 2, 2, 2, 2});
    std::transform(ints1.begin(), ints1.end(), ints2.begin(), ints1.begin (), [](int x, int y) -> int { return x * y; });
    for (int n : ints1)
        std::cout << n;
}
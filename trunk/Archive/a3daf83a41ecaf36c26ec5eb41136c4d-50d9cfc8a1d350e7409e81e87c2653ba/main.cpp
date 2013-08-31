#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> v {5, 10, 7, 8, 90, 21, 453, 5, 234, 432, 765, 978, 214, 4234, 4};

    std::sort(std::begin(v), std::end(v), [](int a, int b) { return b < a; });

    for (auto x : v)
        std::cout << x << std::endl;

    return 0;
}

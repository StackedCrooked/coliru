#include <algorithm>
#include <iostream>

bool f(std::vector<int> v)
{
    return std::is_sorted(begin(v), end(v), std::less_equal<int>());
}

int main()
{
    std::cout << f({1, 2, 3}) << std::endl;
    std::cout << f({1, 2, 2, 3}) << std::endl;
}

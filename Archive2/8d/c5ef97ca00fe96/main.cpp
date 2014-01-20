#include <array>
#include <iostream>

constexpr int sum(std::initializer_list<int> const& l)
{
    auto res = 0;
    for (auto x : l) { res += x; }
    return res;
}

int main()
{
    std::array<int, sum({1, 2, 3})> a;
    std::cout << sizeof(a);
}
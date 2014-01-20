#include <array>
#include <initializer_list>

constexpr int sum(std::initializer_list<int> const& l)
{
    auto int res = 0;
    for (auto x : l) { res += x; }
    return res;
}

int main()
{
    std::array<int, sum({1, 2, 3})> a;
}
#include <iostream>
#include <unordered_set>
#include <vector>

template<typename C>
auto count_unique(C const& c)
{
    auto s = std::unordered_set<typename C::value_type>(std::begin(c), std::end(c));
    return s.size();
}

int main()
{
    auto v = std::vector<int>{1, 2, 3, 2, 1};
    std::cout << count_unique(v);
}
#include <unordered_set>
#include <vector>

std::vector<int> missing_integers(std::vector<int> const& v, int l, int u)
{
    std::vector<int> result;
    std::unordered_set<int> um(v.begin(), v.end());
    for (int i = l; i < u; ++i)
    {
        if (um.find(i) == um.end()) { result.push_back(i); }
    }

    return result;
}

#include <iostream>

int main()
{
    std::vector<int> v { 1, 2, 3, 5 };
    auto result = missing_integers(v, 0, 5);
    for (auto x : result) { std::cout << x << " "; }
}

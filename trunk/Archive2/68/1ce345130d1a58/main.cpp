#include <iostream>
#include <set>
#include <utility>

int main()
{
    auto f = [](std::pair<float, int> const& a, std::pair<float, int> const& b) {
      return a.second < b.second;
    };
    std::multiset<std::pair<float, int>, decltype(f)> m(f);
    
    m.emplace(std::make_pair(3.f, 1));
    m.emplace(std::make_pair(2.f, 1));
    m.emplace(std::make_pair(1.f, 2));
    
    for(auto const& e : m) {
        std::cout << e.first << ' ' << e.second << '\n';
    }
}

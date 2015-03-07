#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <utility>

template <template <typename...> class container, typename... Args>
auto operator << (std::ostream& os, const container<Args...>& cnt) ->
decltype(os << std::begin(cnt)->first, os << std::begin(cnt)->second, os)
{
   for (const auto& p : cnt) os << p.first << "[" << p.second << "]\n";
   return os << "\n";
}

template <template <typename...> class container, typename... Args>
auto operator << (std::ostream& os, const container<Args...>& cnt) ->
decltype(os << *std::begin(cnt), os)
{
   for (const auto& p : cnt) os << p << "\n";
   return os << "\n";
}

int main()
{
   std::map<char, int> map {{'a',5},{'b',5},{'f',3},{'k',8},{'m',5},{'w',8},{'z',1}};
   using pait_t = std::pair<char, int>;
   std::vector<pait_t> vec{map.begin(), map.end()};
   std::multiset<pait_t> set{map.begin(), map.end()};
 
   std::cout << map << vec << set;
   
   std::vector<int> v{1, 2, 3};
   std::cout << v;
}
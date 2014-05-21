#include <iostream>
#include <utility>
#include <string>
 
#include <unordered_map>
int main()
{
    std::unordered_map<std::string, std::string> m;
 
    // uses pair's move constructor (overload 8)
    m.emplace(std::make_pair(std::string("a"), std::string("a")));
 
    // uses pair's converting move constructor (overload 5)
    m.emplace(std::make_pair("b", "abcd"));
 
    // uses pair's template constructor (overload 3)
    m.emplace("d", "ddd");
 
    // uses pair's piecewise constructor (overload 6)
    m.emplace(std::piecewise_construct,
              std::forward_as_tuple("c"),
              std::forward_as_tuple(10, 'c'));
 
    for (const auto &p : m) {
        std::cout << p.first << " => " << p.second << '\n';
    }
}
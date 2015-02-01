#include <iostream>
#include <utility>
#include <string>
 
#include <map>
int main()
{
    std::map<std::string, std::string> m;
 
    // uses pair's move constructor
    std::pair<std::string, std::string> lol = m.emplace(std::make_pair(std::string("a"), std::string("a")));
    std::cout << lol << std::endl;
 
    for (const auto &p : m) {
        std::cout << p.first << " => " << p.second << '\n';
    }
}
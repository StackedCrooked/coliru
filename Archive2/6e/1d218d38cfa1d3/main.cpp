#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int main()
{
    std::unordered_map<std::string, std::vector<std::string>> map = { { "XXX", { "A", "B" } }, { "YYY", { "C", "D", "E" } } };
    
    auto it = map.find("XXX");
    bool process = it != map.end();
    if (process)
    {
        auto subIt = std::find(it->second.begin(), it->second.end(), "B");
        process &= subIt == it->second.end();
    }
    
    std::cout << std::boolalpha << process << std::endl;
    
    return 0;
}
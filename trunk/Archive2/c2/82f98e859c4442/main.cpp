#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::map<int, std::string> myMap = { { 2, "foo" }, { 3, "bar" } };
    
    std::vector<std::string> vec(myMap.size());
    std::transform(myMap.begin(), myMap.end(), std::back_inserter(vec), [](std::pair<int, std::string>& entry) { return entry.second; });
    
    for (auto& s : vec) { std::cout << s << " "; }
    
    return 0;
}
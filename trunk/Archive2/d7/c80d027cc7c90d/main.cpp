#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>

int main()
{
    std::vector<char> mykeys { 'a', 'b', 'c' };
    std::map<char, int> myMap;
    
    std::transform(std::begin(mykeys), std::end(mykeys), std::begin(myMap),
    [](const char c) { return std::pair<char,int>(c, 0); });

    for (auto p : myMap)
        std::cout << p.first << ' ' << p.second << '\n';
}

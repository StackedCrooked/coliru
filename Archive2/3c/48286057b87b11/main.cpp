#include <iostream>
#include <unordered_map>
 
int main()
{  
    std::unordered_multimap<int,char> map = {{1,'a'},{1,'b'},{1,'d'},{2,'b'}};
    auto range = map.equal_range(1);
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->first << ' ' << it->second << '\n';
    }
}